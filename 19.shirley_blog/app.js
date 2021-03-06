var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var session = require('express-session');

var indexRouter = require('./routes/index');
var listRouter = require('./routes/list');
var adminRouter = require('./routes/admin');

var databsse = require('./utils/database');

var app = express();

app.set('trust proxy', 1) // trust first proxy
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use(session({
  secret: 'd2LpRLPxmb0tp2yM',
  resave: false,
  saveUninitialized: true,
  cookie: {
  	maxAge : 1000 * 60 * 30 //半小时无操作视为用户退出
  }
}));

//初始化MySQL连接池
databsse.Initialize();

//允许跨域请求json
app.all('*', function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "X-Requested-With");
    res.header("Access-Control-Allow-Methods", "PUT,POST,GET,DELETE,OPTIONS");
    //res.header("X-Powered-By", ' 3.2.1')
    //这段仅仅为了方便返回json而已
    //res.header("Content-Type", "application/json;charset=utf-8");
    if(req.method == 'OPTIONS') {
        //让options请求快速返回
        res.sendStatus(200); 
    } else { 
        next(); 
    }
});

app.use('/', indexRouter);
app.use('/list', listRouter);
app.use('/admin', adminRouter);

module.exports = app;
