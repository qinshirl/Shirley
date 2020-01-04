var express = require('express');
var router = express.Router()
var fs = require("fs");
var path = require('path');
var formidable = require('formidable');
var database = require('./database')

function SendErrJson(res, err) {
	var result = {
		code: 1, //TODO: 非零应该表示具体错误是什么，这里如果出错先统一返回1
		msg: err ? err.message : "Unknown Error"
	};
	res.send(JSON.stringify(result));
}

var auth = function(req, res, next) {
	//鉴定用户
	if(req.session.authorized === 1) {
		return next();
	} else {
		var result = {
			code: -1,
			msg: "登录超时，请<a href=\"#\" onclick=\"top.location.href='/admin/login.htm';window.location.href='/admin/login.htm';\"><font color='red'>重新登录</font></a>"
		};
		return res.send(JSON.stringify(result));
	}

	return next();
}

router.get('/login', function(req, res, next) {
	var sql = 'select * from blog_user where `name` = ?';
	var params = [req.query.username];

	database.QueryMySQL(sql, params).then(
		function (result) {
			if (result[0] && result[0].password === req.query.password) {
				req.session.authorized = 1;
				res.redirect('/admin/list.htm');
			} else {
				res.redirect('/admin/login.htm');
			}
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

router.post('/add', auth, function(req, res, next) {

	var category = req.body.category;
	var title = req.body.title;
	var summary = req.body.summary;
	var body = req.body.tx_body;

	var sql = 'INSERT INTO blog_article(title, category, summary, body) VALUES(?,?,?,?)';
	var params = [title, category, summary, body];

	database.QueryMySQL( sql, params ).then(
		function (result) {
			var ret_obj = {
				code: 0
			};
			res.send(JSON.stringify(ret_obj))
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

router.post('/update', auth, function(req, res, next) {

	var id = req.body.id;
	var category = req.body.category;
	var title = req.body.title;
	var summary = req.body.summary;
	var body = req.body.tx_body;

	var sql = 'UPDATE blog_article set title = ?, category = ?, summary = ?, body = ? where id = ?';
	var params = [title, category, summary, body, id];

	database.QueryMySQL( sql, params ).then(
		function (result) {
			var ret_obj = {
				code: 0
			};
			res.send(JSON.stringify(ret_obj))
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

router.get('/list', auth, function(req, res, next) {
	//从第几页开始
	var CurrentPage = req.query.page ? parseInt(req.query.page) : 1;

	//每一页加载NumbersPerPage篇
	var NumbersPerPage = req.query.limit ? parseInt(req.query.limit) : 20;

	//在数据库里面应该是从第几条开始，从URL参数里面取出来
	var Start = CurrentPage * NumbersPerPage - NumbersPerPage;

	var sql = 'SELECT count(*) as count from blog_article';
	var count = 0;

	database.QueryMySQL( sql ).then(
		function (result) {
			count = result[0].count;
			var sql = 'SELECT id, title FROM blog_article ORDER BY id desc limit ?,?';
			var params = [Start, NumbersPerPage];

			return database.QueryMySQL( sql, params );
		}
	).then(
		function (result) {
			var ret_obj = {
				code: 0,
				msg: "",
				count: count,
				data: result
			};
			res.send(JSON.stringify(ret_obj));
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

router.get('/category_list', auth, function(req, res, next) {
	var sql = 'SELECT * from blog_category';

	database.QueryMySQL( sql ).then(
		function (result) {
			var ret_obj = {
				code: 0,
				data: result
			};
			res.send(JSON.stringify(ret_obj));
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

router.get(/^\/delete\/id\/([1-9]{1}[0-9]*)$/, auth, function(req, res, next) {
	var sql = 'delete FROM blog_article where id = ?';
	var params = [parseInt(req.params[0])];

	database.QueryMySQL( sql, params ).then(
		function (result) {
			var ret_obj = {
				code: 0
			};
			res.send(JSON.stringify(ret_obj));
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

router.get(/^\/detail\/id\/([1-9]{1}[0-9]*)$/, auth, function(req, res, next) {
	var sql = 'SELECT * from blog_article where id = ?';
	var params = [parseInt(req.params[0])];

	database.QueryMySQL( sql, params ).then(
		function (result) {
			var ret_obj = {
				code: 0,
				data: result
			};
			res.send(JSON.stringify(ret_obj));
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

function dateFtt(fmt, date) { //author: meizz   
	var o = {
		"M+": date.getMonth() + 1, //月份   
		"d+": date.getDate(), //日   
		"h+": date.getHours(), //小时   
		"m+": date.getMinutes(), //分   
		"s+": date.getSeconds(), //秒   
		"q+": Math.floor((date.getMonth() + 3) / 3), //季度   
		"S": date.getMilliseconds() //毫秒   
	};
	if(/(y+)/.test(fmt))
		fmt = fmt.replace(RegExp.$1, (date.getFullYear() + "").substr(4 - RegExp.$1.length));
	for(var k in o)
		if(new RegExp("(" + k + ")").test(fmt))
			fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
	return fmt;
}

//创建时间格式化显示
function crtTimeFtt() {
	var crtTime = new Date();
	return dateFtt("yyyy-MM-dd hh:mm:ss", crtTime); //直接调用公共JS里面的时间类处理的办法     
}

function mkdirsSync(dirpath, mode) {
	if(!fs.existsSync(dirpath)) {
		var pathtmp;
		dirpath.split(path.sep).forEach(function(dirname) {
			if(dirname == "") {
				dirname = "/"
			}
			if(pathtmp) {
				pathtmp = path.join(pathtmp, dirname);
			} else {
				pathtmp = dirname;
			}
			if(!fs.existsSync(pathtmp)) {
				if(!fs.mkdirSync(pathtmp, mode)) {
					return false;
				}
			}
		});
	}
	return true;
}

router.post('/upload_image', auth, function(req, res) {

	var today = new Date();
	var folder = today.getFullYear() + "" + (today.getMonth() + 1) + "" + today.getDate();
	var dirname = __dirname.replace('routes', 'public/uploads/' + folder);

	if(mkdirsSync(dirname, '0777')) {
		var form = new formidable.IncomingForm();
		form.encoding = "utf-8";
		form.uploadDir = dirname;
		form.maxFontSize = 2 * 1024 * 1024;
		form.parse(req, function(err, fields, files) {
			if(err) {
				var result = {
					uploaded: 0,
					msg: err.message
				};
				res.end(JSON.stringify(result));
			};
			var fileName = new Date().getTime() + "." + files.upload.name.split('.')[files.upload.name.split('.').length - 1];
			var newPath = form.uploadDir + "/" + fileName;
			fs.rename(files.upload.path, newPath, function() {
				var result = {
					uploaded: 1,
					fileName: fileName,
					url: '/uploads/' + folder + "/" + fileName
				};
				res.end(JSON.stringify(result));
			});
		})
	} else {
		var result = {
			uploaded: 0,
			msg: err.message
		};
		res.end(JSON.stringify(result));
	}
})

module.exports = router;