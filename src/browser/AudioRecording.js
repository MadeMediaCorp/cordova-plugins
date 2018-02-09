exports.recorder = null;
exports.recorderURL = null;

exports.startRecording = function(success, error) {
    exports.recorder = new Recorder({
        encoderApplication: 2048,
        encoderComplexity: 5,
        encoderPath: 'plugins/spark-plugin-audio-recording/www/browser/encoderWorker.min.js',
        encoderSampleRate: 8000
    });

    var promise = exports.recorder.initStream();
    
    promise.then(function(s) {
        if(s) {
            exports.recorder.start();
            success('success');
        }
        else {
            error('could not start');
        }
        
    })
    .catch(function(reason) {
        error(reason);
    });
};
exports.prepareRecording = function(success, error) {
    // NOT SUPPORTED
}
exports.isPaused = function(success, error) {
    // NOT SUPPORTED
};

exports.isRecording = function(success, error) {
    // NOT SUPPORTED
};

exports.closeSession = function(success, error) {
    // NOT SUPPORTED
};

exports.pauseRecording = function(success, error) {
    //NOT IMPLEMENTED
};

exports.resumeRecording = function(success, error) {
    //NOT IMPLEMENTED
};

exports.stopRecording = function(success, error) {
    if(exports.recorder) {
        exports.recorder.addEventListener('dataAvailable', function(e) {
            var dataBlob = new Blob( [e.detail], { type: 'audio/ogg' } );
            var fileName = Date.now()+'.ogg';
            var url = URL.createObjectURL( dataBlob );
            exports.recorderURL = url;

            exports.recorder.audioContext.close();
            exports.recorder.clearStream();
            exports.recorder = null;
            success(url);
        });

        exports.recorder.stop();
    }
    else {
        success(null);
    }
};

exports.getRecording = function(success, error) {
    success(exports.recorderURL);
};

exports.destroyRecording = function(success, error) {
    exports.recorder = null;
}