var express = require('express');
var router = express.Router();

router.get("/", function(req, res, next) {
    res.redirect('index.htm');
});

module.exports = router;