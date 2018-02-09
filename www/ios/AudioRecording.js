var exec = require('cordova/exec');

exports.initialize = function() {
	function afterPrepareRecording(d) {
		cordova.plugins.AudioRecording.resumeRecording(function(){}, function(){});
	};

	function afterReset(c) {
		cordova.plugins.AudioRecording.prepareRecording(afterPrepareRecording, afterPrepareRecording);
	};

	function afterPrepareSwiper(b) {
		Spark.scanners.ccSwipe.reset(afterReset, afterReset);
	};

	function afterPause(a) {	
		Spark.scanners.ccSwipe.prepareSwiper(afterPrepareSwiper, afterPrepareSwiper);
	};

    window.broadcaster.addEventListener( "AppRouteChanged", function(res) {
    	cordova.plugins.AudioRecording.pauseRecording(afterPause, afterPause);
    });
}
exports.prepareRecording = function(success, error) {
	execPreparation = function(t) {
		exec(success, error, "SparkAudio", "prepareRecording", ['']);
	};
	Spark.scanners.ccSwipe.turnOff(execPreparation, execPreparation);
	
};
exports.startRecording = function(success, error) {
    exec(success, error, "SparkAudio", "startRecording", ['']);
};
exports.stopRecording = function(success, error) {
    exec(success, error, "SparkAudio", "stopRecording", ['']);
};

exports.pauseRecording = function(success, error) {
    exec(success, error, "SparkAudio", "pauseRecording", ['']);
};

exports.resumeRecording = function(success, error) {
    exec(success, error, "SparkAudio", "resumeRecording", ['']);
};

exports.isPaused = function(success, error) {
    exec(success, error, "SparkAudio", "isPaused", ['']);
};

exports.isRecording = function(success, error) {
    exec(success, error, "SparkAudio", "isRecording", ['']);
};
exports.closeSession = function(success, error) {
    exec(success, error, "SparkAudio", "closeSession", ['']);
};

exports.getRecording = function(success, error) {
    exec(success, error, "SparkAudio", "get", ['']);
};

exports.destroyRecording = function(success, error) {
    exec(success, error, "SparkAudio", "del", ['']);
}
