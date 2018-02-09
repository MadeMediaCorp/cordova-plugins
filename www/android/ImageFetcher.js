var exec = require('cordova/exec');

exports.download = function(images, campaign, success, error) {
    exec(success, error, "ImageFetcher", "download", [images, campaign]);
};