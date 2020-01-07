var config = require('config');
var mysql = require('mysql');

var connection = null;

module.exports.Initialize = function () {
    if (connection === null) {
        var config_mysql = config.get('db.mysql');
        connection = mysql.createPool({
            host: config_mysql.host,
            user: config_mysql.user,
            password: config_mysql.password,
            database: config_mysql.database,
            connectionLimit: config_mysql.max_connections,
            multipleStatements: false, //允许一次性执行多个SQL语句，开启可能导致安全问题，故此处禁用
        });

        console.log('MySQL Pool Have Been Inited.')
    }
};

module.exports.QueryMySQL = function () {
    var local_arguments = arguments;

    return new Promise(function (resolve, reject) {
        if (!connection) {
            return reject('MySQL Pool Have Not Been Inited.');
        }

        if (local_arguments.length !== 1 && local_arguments.length !== 2) {
            return reject('Wrong arguments number');
        }

        var sql = local_arguments[0];
        var params = local_arguments[1];
        if (typeof (params) !== 'object') {
            connection.query(sql, function (err, result) {
                if (err) {
                    reject(err)
                } else {
                    resolve(result)
                }
            });
        } else {
            connection.query(sql, params, function (err, result) {
                if (err) {
                    reject(err)
                } else {
                    resolve(result)
                }
            });
        }
    });
}