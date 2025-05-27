#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#define PAUSE 13
#define NEXT 12
#define PREVIOUS 14

AnalogAudioStream out;
BluetoothA2DPSink a2dp_sink(out);

void setup() {
    a2dp_sink.set_auto_reconnect(true);
    a2dp_sink.start("Panasonic Stereo Music System");
    a2dp_sink.set_volume(100); // Set initial volume to 50%
    pinMode(PAUSE, INPUT_PULLUP);
    pinMode(NEXT, INPUT_PULLUP);
    pinMode(PREVIOUS, INPUT_PULLUP);
}

bool isPaused = false;
bool prevPause = false;
bool prevNext = false;
bool prevPrevious = false;
void loop() {
    bool pause = !digitalRead(PAUSE);
    bool next = !digitalRead(NEXT);
    bool previous = !digitalRead(PREVIOUS);
    if (prevPause) {
        // Button was released
        if (!pause) prevPause = false;
    }
    else if (pause) {
        if (isPaused) a2dp_sink.play();
        else a2dp_sink.pause();
        isPaused = !isPaused;
        prevPause = true;
    }
    if (prevNext) {
        // Button was released
        if (!next) prevNext = false;
    }
    else if (next) {
        a2dp_sink.next();
        prevNext = true;
    }
    
    if (prevPrevious) {
        // Button was released
        if (!previous) prevPrevious = false;
    }
    else if (previous) {
        a2dp_sink.previous();
        prevPrevious = true;
    }
}