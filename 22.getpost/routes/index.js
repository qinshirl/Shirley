var mysql = require('mysql');
var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.send("shirley");
});




router.get('/test_1', function (req, res){
  var connection = mysql.createConnection({
    host: '192.168.1.78',
    user: 'root',
    password: 'root',
    database: 'shirley'
  });

  connection.connect();

  var sql = 'SELECT * FROM `grade` ';
  var params = [req.params[0], req.params[1]];

  connection.query(sql, params, function (error, results) {
    if (error) {
      console.log(error);
      return;
      //throw error;
    }
    //console.log('The solution is: ', results);
    res.send(results);
  });

  connection.end();

})

module.exports = router;