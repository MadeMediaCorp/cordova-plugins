var exec = require('cordova/exec');

exports.prepareRecording = function(success, error) {
	error('Not supported');
};

exports.isPaused = function(success, error) {
    error('Not supported');
};

exports.isRecording = function(success, error) {
    error('Not supported');
};

exports.closeSession = function(success, error) {
    error('Not supported');
};

exports.startRecording = function(success, error, title, description) {
    exec(success, error, "AudioRecording", "start", [title, description]);
};

exports.pauseRecording = function(success, error) {
    exec(success, error, "AudioRecording", "pause", ['']);
};

exports.resumeRecording = function(success, error) {
    exec(success, error, "AudioRecording", "resume", ['']);
};

exports.stopRecording = function(success, error) {
    exec(success, error, "AudioRecording", "stop", ['']);
};

exports.getRecording = function(success, error) {
    exec(success, error, "AudioRecording", "get", ['']);
};

exports.destroyRecording = function(success, error) {
    exec(success, error, "AudioRecording", "del", ['']);
}