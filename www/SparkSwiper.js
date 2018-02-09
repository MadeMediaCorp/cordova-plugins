var exec = require('cordova/exec');


exports.prepareSwiper = function(success, error) {
    exec(success, error, "SparkSwiper", "prepareSwiper", ['']);
}
exports.turnOff = function(success, error) {
    exec(success, error, "SparkSwiper", "turnOff", ['']);
}
exports.reset = function(success, error) {
    exec(success, error, "SparkSwiper", "reset", ['']);
}
exports.stopWaitingForCard = function(success, error) {
    exec(success, error, "SparkSwiper", "stopWaitingForCard", ['']);
}
exports.collectCard = function(success, error, listener) {
	var isListening = false;
	if (listener && typeof listener == "function") {
		isListening = true;
		window.broadcaster.addEventListener( "swiperMessage", listener);
	}
	
    function successWrapper(res) {
    	if (isListening) { window.broadcaster.removeEventListener( "swiperMessage", listener); }
    	res = JSON.parse(res);
    	success.call(this, res);
    }

    function errorWrapper(res) {
    	if (isListening) { window.broadcaster.removeEventListener( "swiperMessage", listener); }
    	error.call(this, res);
    }

    // Adding listener need some time.
    setTimeout( function() {
        exec(successWrapper, errorWrapper, "SparkSwiper", "collectCard", ['']);
    }, 800);
    
};