var express = require('express');
var router = express.Router();
var database = require('../utils/database')

function SendErrJson(res, err) {
	var result = {
		code: 1, //TODO: 非零应该表示具体错误是什么，这里如果出错先统一返回1
		msg: err ? err.message : "Unknown Error"
	};
	res.send(JSON.stringify(result));
}

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

//全部文章，分页
router.get(/^\/page\/([1-9]{1}[0-9]*)\/category\/([0-9]*)$/, function(req, res, next) {
	//第几页
	var CurrentPage = parseInt(req.params[0]);
	var CurrentCategory = parseInt(req.params[1]);

	//文章列表，每一页加载10篇
	var NumbersPerPage = 10

	//在数据库里面应该是从第几条开始，从URL参数里面取出来
	var Start = CurrentPage * NumbersPerPage - NumbersPerPage;

	var sql = null;
	var param = null;
	if(CurrentCategory == 0){
		sql = 'SELECT count(*) as count from blog_article';
		params = [];
	}
	else{
		sql = 'SELECT count(*) as count from blog_article where category = ?';
		params = [CurrentCategory];
	}

	var count = 0;
	database.QueryMySQL( sql, params ).then(
		function (result) {
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
			return database.QueryMySQL( sql, params );
		}
	).then(
		function ( result ) {
			//格式化时间的格式
			for ( var nIndex = 0; nIndex < result.length; nIndex++ )
			{
				result[nIndex].time = result[nIndex].time.Format("yyyy/MM/dd HH:mm:ss");
			}
			var ret_obj = {
				code: 0,
				count: count,
				data: result,
			};
			res.send(JSON.stringify(ret_obj));
		}
	).catch(
		function (err) {
			SendErrJson(res, err);
		}
	)
});

//文章详情
router.get(/^\/article\/([1-9]{1}[0-9]*)$/, function(req, res, next) {

	var sql = 'SELECT blog_article.id, blog_category.name as category, title, body, time FROM blog_article ' +
		'LEFT JOIN blog_category ON blog_article.category = blog_category.id where blog_article.id = ?';
	var params = [parseInt(req.params[0])];

	database.QueryMySQL( sql, params ).then(
		function (result) {
			if ( !result.length )
			{
				var result = {
					code: 1,
					msg: "not exist"
				};
				res.send(JSON.stringify(result));
				return;
			}
			result[0].time = result[0].time.Format("yyyy/MM/dd HH:mm:ss");
			var ret_obj = {
				code: 0,
				msg: "",
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

router.get('/category', function(req, res, next) {
	var sql = 'SELECT * from blog_category order by id desc';

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

//最新文章，不分页
router.get('/latest', function (req, res, next) {
	var sql = 'SELECT id, title FROM blog_article order by id desc limit 0, 20';

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

module.exports = router;