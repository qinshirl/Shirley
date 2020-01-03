var express = require('express');
var router = express.Router();
var config = require('config');
var mysql = require('mysql');

Date.prototype.Format = function(fmt){
	var o = {
		"M+": this.getMonth()+1,
		"d+": this.getDate(),
		"H+": this.getHours(),
		"m+": this.getMinutes(),
		"s+": this.getSeconds(),
		"S+": this.getMilliseconds()
	};
	//因为date.getFullYear()出来的结果是number类型的,所以为了让结果变成字符串型，下面有两种方法：
	if(/(y+)/.test(fmt)){
		//第一种：利用字符串连接符“+”给date.getFullYear()+""，加一个空字符串便可以将number类型转换成字符串。
		fmt=fmt.replace(RegExp.$1,(this.getFullYear()+"").substr(4-RegExp.$1.length));
	}
	for(var k in o){
		if (new RegExp("(" + k +")").test(fmt)){
			//第二种：使用String()类型进行强制数据类型转换String(date.getFullYear())，这种更容易理解。
			fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(String(o[k]).length)));
		}
	}
	return fmt;
};

function CreateMySQLConnection() {
	var config_mysql = config.get('db.mysql');
	return mysql.createConnection({
		host: config_mysql.host,
		user: config_mysql.user,
		password: config_mysql.password,
		database: config_mysql.database
	});
}

//全部文章，分页
router.get(/^\/page\/([1-9]{1}[0-9]*)\/category\/([0-9]*)$/, function(req, res, next) {
	//第几页
	var CurrentPage = parseInt(req.params[0]);
	var CurrentCategory = parseInt(req.params[1]);

	//文章列表，每一页加载10篇
	var NumbersPerPage = 10

	//在数据库里面应该是从第几条开始，从URL参数里面取出来
	var Start = CurrentPage * NumbersPerPage - NumbersPerPage;

	var connection = CreateMySQLConnection();
	connection.connect();

	var sql = null;
	var param = null;
	if(CurrentCategory == 0){
		sql = 'SELECT count(*) as count from blog_article';
		param = [];
	}
	else{
		sql = 'SELECT count(*) as count from blog_article where category = ?';
		param = [CurrentCategory];
	}

	var count = 0;
	connection.query(sql, param, function(err, result) {
		if (err) {
			var result = {
				statu: 0,
				msg: err.message
			};
			res.send(JSON.stringify(result));
			connection.end();
		} else {
			count = result[0].count;

			var sql = null;
			var param = null;
			if(CurrentCategory == 0){
				var sql = 'SELECT blog_article.id, blog_category.name as category, title, summary, time FROM blog_article ' +
					'LEFT JOIN blog_category ON blog_article.category = blog_category.id order by blog_article.id desc limit ?,?';
				var params = [Start, NumbersPerPage];
			}
			else{
				var sql = 'SELECT blog_article.id, blog_category.name as category, title, summary, time FROM blog_article LEFT JOIN blog_category ON blog_article.category = blog_category.id where blog_article.category = ? order by blog_article.id desc limit ?,?';
				var params = [CurrentCategory, Start, NumbersPerPage];
			}

			connection.query(sql, params, function(err, result) {
				if(err) {
					res.send('[MYSQL ERROR] - ' + err.message);
				} else {
					result.count = count;
					//格式化时间的格式
					for ( var nIndex = 0; nIndex < result.length; nIndex++ )
					{
						result[nIndex].time = result[nIndex].time.Format("yyyy/MM/dd HH:mm:ss");
					}
					res.send(JSON.stringify(result));
				}
			});

			connection.end();
		}
	});
});

//文章详情
router.get(/^\/article\/([1-9]{1}[0-9]*)$/, function(req, res, next) {
	var connection = CreateMySQLConnection();
	connection.connect();

	var sql = 'SELECT * from blog_article where id = ?';
	var params = [parseInt(req.params[0])];
	connection.query(sql, params, function(err, result) {
		if(err) {
			var result = {
				code: 1,
				msg: err.message
			};
			res.send(JSON.stringify(result));
			connection.end();
		} else {
			var ret_obj = {
				code: 0,
				msg: "",
				data: result
			};
			res.send(JSON.stringify(ret_obj));
			connection.end();
		}
	});
});

router.get('/category', function(req, res, next) {
	var connection = CreateMySQLConnection();
	connection.connect();

	var sql = 'SELECT * from blog_category order by id desc';
	connection.query(sql, function(err, result) {
		if(err) {
			var result = {
				code: 1,
				msg: err.message
			};
			res.send(JSON.stringify(result));
			connection.end();
		} else {
			var ret_obj = {
				code: 0,
				data: result
			};
			res.send(JSON.stringify(ret_obj));

			connection.end();
		}
	});
});

//最新文章，不分页
router.get('/latest', function (req, res, next) {
	var connection = CreateMySQLConnection();
	connection.connect();

	var sql = 'SELECT id, title FROM blog_article order by id desc limit 0, 20';
	connection.query(sql, function (err, result) {
		if (err) {
			res.send('[MYSQL ERROR] - ' + err.message);
			connection.end();
		} else {
			res.send(JSON.stringify(result));
			connection.end();
		}
	});
});

module.exports = router;