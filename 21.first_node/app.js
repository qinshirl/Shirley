var express = require('express');
var app = express();
var bodyParser = require('body-parser')
app.use(bodyParser.urlencoded({ extended: false }))
app.use(bodyParser.json())


app.get('/', function (req, res) {
    res.send('Hello World');
})

//app.get('/shirley', function (req, res) {
app.get(/^\/shirley\/([0-9]*)$/, function (req, res) {

    res.send( req.params[0] );

})

app.use('/public', express.static('public'));

// app.get(/^\/mysql_test\/([0-9]*)\/([a-z A-Z]*)$/, function (req, res){
 app.get(/^ \/mysql_test\/([0-9]*)\/([a-z A-Z\W]*)$/, function (req, res){
    var mysql      = require('mysql');
    var connection = mysql.createConnection({
        host     : '192.168.1.78',
        user     : 'root',
        password : 'root',
        database : 'shirley'
    });

     connection.connect();

     // var sql = 'SELECT * FROM `websites` where `id` = ? and `name` = ?'
     var sql = 'SELECT * FROM `websites` order by id DESC where `alexa` = ? and `url` = ?';
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

app.get('/all_data', function (req, res){
    var mysql      = require('mysql');
    var connection = mysql.createConnection({
        host     : '192.168.1.78',
        user     : 'root',
        password : 'root',
        database : 'shirley'
    });

    connection.connect();

    var sql = 'SELECT * FROM `websites` ';
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

//get demo
app.get('/getDemo', function (req, res) {

    console.log(req);
    //console.log(req.query.id);

    res.send("jjjj");

})

//post demo
app.post('/postDemo', function (req, res) {

    console.log(req.body);
    //console.log(req.query.id);

    res.send("111111");

})

var server = app.listen(80);