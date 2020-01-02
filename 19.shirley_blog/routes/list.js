var express = require('express');
var router = express.Router();
var config = require('config');
var mysql = require('mysql');

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
router.get(/^\/page\/([1-9]{1}[0-9]*)$/, function(req, res, next) {
	//第几页
	var CurrentPage = parseInt(req.params[0]);

	//文章列表，每一页加载5篇
	var NumbersPerPage = 5;

	//在数据库里面应该是从第几条开始，从URL参数里面取出来
	var Start = CurrentPage * NumbersPerPage - NumbersPerPage;

	var connection = CreateMySQLConnection();
	connection.connect();

	var sql = 'SELECT id, category, title, summary, time FROM blog_article ORDER BY id desc limit ?,?';
	var params = [Start, NumbersPerPage];
	connection.query(sql, params, function(err, result) {
		if(err) {
			res.send('[MYSQL ERROR] - ' + err.message);
		} else {
			res.send(JSON.stringify(result));
		}
	});

	connection.end();
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

module.exports = router;