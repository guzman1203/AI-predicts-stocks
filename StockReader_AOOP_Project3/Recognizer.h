#pragma once

#include "SmartCandleStick.h"
#include <math.h>

using namespace System;
using namespace System::Collections::Generic;

// Abstract base class for all recognizers
public ref class Recognizer abstract {

public: List<int>^ indexList = gcnew List<int>();
public: virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) abstract;

};

// Recognize Bearish
public ref class BearishRecognizer : public Recognizer {

public:

    BearishRecognizer() {}

    // Recognize bearish candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isBear)
            indexList->Add(loc);
    }
};

// Recognize Bullish
public ref class BullishRecognizer : public Recognizer {

public:

    BullishRecognizer() {}

    // Recognize bullish candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isBull)
            indexList->Add(loc);
    }
};

// Recognize Neutral
public ref class NeutralRecognizer : public Recognizer {

public:

    NeutralRecognizer() {}

    // Recognize neutral candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isNeu)
            indexList->Add(loc);
    }
};

// Recognize Marubuzo
public ref class MarubuzoRecognizer : public Recognizer {

public:

    MarubuzoRecognizer() {}

    // Recognize marubuzo candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isMaru)
            indexList->Add(loc);
    }
};

// Recognize Bearish Marubuzo
public ref class BearishMarubuzoRecognizer : public Recognizer {

public:

    BearishMarubuzoRecognizer() {}

    // Recognize bearish marubuzo candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isBearMaru)
            indexList->Add(loc);
    }
};

// Recognize Bullish Marubuzo
public ref class BullishMarubuzoRecognizer : public Recognizer {

public:

    BullishMarubuzoRecognizer() {}

    // Recognize bullish marubuzo candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isBullMaru)
            indexList->Add(loc);
    }
};

// Recognize Doji
public ref class DojiRecognizer : public Recognizer {

public:

    DojiRecognizer() {}

    // Recognize doji candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isDoj)
            indexList->Add(loc);
    }
};

// Recognize Gravestone Doji
public ref class GravestoneDojiRecognizer : public Recognizer {

public:

    GravestoneDojiRecognizer() {}

    // Recognize gravestone doji candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isDragonFly)
            indexList->Add(loc);
    }
};

// Recognize Dragonfly Doji
public ref class DragonflyDojiRecognizer : public Recognizer {

public:

    DragonflyDojiRecognizer() {}

    // Recognize dragonfly doji candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isGraveStone)
            indexList->Add(loc);
    }
};

// Recognize Hammer
public ref class HammerRecognizer : public Recognizer {

public:

    HammerRecognizer() {}

    // Recognize hammer candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isHamm)
            indexList->Add(loc);
    }
};

// Recognize Inverted Hammer
public ref class InvertedHammerRecognizer : public Recognizer {

public:

    InvertedHammerRecognizer() {}

    // Recognize inverted hammer candlestick patterns
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (listOfSMS[glob]->isInvertedHamm)
            indexList->Add(loc);
    }
};

// Recognize Engulfing
public ref class EngulfingRecognizer : public Recognizer {

public:

    EngulfingRecognizer() {}

    // determines if engulfing and adds both indexes
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (isEngulfing(listOfSMS, glob)) {
            indexList->Add(loc);
            indexList->Add(loc + 1);
        }
    }

    // determines if engulfing
    bool isEngulfing(List<SmartCandleStick^>^ listOfSMS, int glob) {
        bool result = false;
        if (glob >= listOfSMS->Count - 1)
            return result;
        else if (
            listOfSMS[glob + 1]->high > listOfSMS[glob]->high && //2nds high > 1sts high
            listOfSMS[glob + 1]->low < listOfSMS[glob]->low &&   //2nds low < 1sts low
            listOfSMS[glob + 1]->topPrice > listOfSMS[glob]->topPrice &&       //2nds body upper > 1sts body upper
            listOfSMS[glob + 1]->bottomPrice < listOfSMS[glob]->bottomPrice)  //2nds body upper > 1sts body upper
            result = true;
        return result;
    }

};// Recognize Bearish Engulfing
public ref class BearishEngulfingRecognizer : public Recognizer {

public:

    BearishEngulfingRecognizer() {}

    // determines if bearish engulfing and adds both indexes
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (isBearishEngulfing(listOfSMS, glob)) {
            indexList->Add(loc);
            indexList->Add(loc + 1);
        }
    }

    // determines if bearish engulfing
    bool isBearishEngulfing(List<SmartCandleStick^>^ listOfSMS, int glob) {
        bool result = false;
        if (glob >= listOfSMS->Count - 1)
            return false;
        else if (
            listOfSMS[glob]->isBull &&      //1st is bullish
            listOfSMS[glob + 1]->isBear &&  //2nd is bearish
            listOfSMS[glob + 1]->high > listOfSMS[glob]->high &&  //2nds high > 1sts high
            listOfSMS[glob + 1]->low < listOfSMS[glob]->low &&    //2nds low < 1sts low
            listOfSMS[glob + 1]->topPrice > listOfSMS[glob]->topPrice &&       //2nds body upper > 1sts body upper
            listOfSMS[glob + 1]->bottomPrice < listOfSMS[glob]->bottomPrice )  //2nds body upper > 1sts body upper
            result = true;
        return result;
    }
};


// Recognize Bullish Engulfing
public ref class BullishEngulfingRecognizer : public Recognizer {

public:

    BullishEngulfingRecognizer() {}

    // determines if bullish engulfing and adds both indexes
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (isBullishEngulfing(listOfSMS, glob)) {
            indexList->Add(loc);
            indexList->Add(loc+1);
        }
    }

    // determines if bullish engulfing
    bool isBullishEngulfing(List<SmartCandleStick^>^ listOfSMS, int glob) {
        bool result = false;
        if (glob >= listOfSMS->Count - 1)
            return result;
        else if (
            listOfSMS[glob]->isBear &&      //1st is bearish
            listOfSMS[glob + 1]->isBull &&  //2nd is bullish
            listOfSMS[glob + 1]->high > listOfSMS[glob]->high &&  //2nds high > 1sts high
            listOfSMS[glob + 1]->low < listOfSMS[glob]->low &&    //2nds low < 1sts low
            listOfSMS[glob + 1]->topPrice > listOfSMS[glob]->topPrice &&      //2nds body upper > 1sts body upper
            listOfSMS[glob + 1]->bottomPrice < listOfSMS[glob]->bottomPrice)  //2nds body upper > 1sts body upper
            result = true;
        return result;
    }
};

// Recognize Bearish Harami
public ref class BearishHaramiRecognizer : public Recognizer {

private:
    double harmaiMod = 0.34;

public:

    BearishHaramiRecognizer() {}

    // finds the pregnant candle sticks and adds both indexes
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (isBearishHarami(listOfSMS, glob)) {
            indexList->Add(loc);
            indexList->Add(loc + 1);
        }
    }
    // finds the pregnant candle sticks 
    bool isBearishHarami(List<SmartCandleStick^>^ listOfSMS, int glob) {
        bool result = false;
        if (glob >= listOfSMS->Count - 1)
            return false;
        else if (
            listOfSMS[glob]->isBull &&      //1st is bullish
            listOfSMS[glob + 1]->isBear &&  //2nd is bearish
            listOfSMS[glob + 1]->bodyRange / listOfSMS[glob]->bodyRange <= harmaiMod && // 2nds body range / 1sts body range <= haramiMod 
            listOfSMS[glob + 1]->open < listOfSMS[glob]->close) //gap down: 2nds open < 1sts close
            result = true;
        return result;
    }
};

// Recognize Bullish Harami
public ref class BullishHaramiRecognizer : public Recognizer {

private:
    double harmaiMod = 0.34;

public:

    BullishHaramiRecognizer() {}

    // finds the pregnant candle sticks and adds both indexes
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (isBullishHarami(listOfSMS, glob)) {
            indexList->Add(loc);
            indexList->Add(loc + 1);
        }
    }

    // finds the pregnant candle sticks
    bool isBullishHarami(List<SmartCandleStick^>^ listOfSMS, int glob) {
        bool result = false;
        if (glob >= listOfSMS->Count - 1)
            return false;
        else if (
            listOfSMS[glob]->isBear &&      //1st is bullish
            listOfSMS[glob + 1]->isBull &&  //2nd is bearish
            listOfSMS[glob + 1]->bodyRange / listOfSMS[glob]->bodyRange <= harmaiMod && // 2nds body range / 1sts body range <= haramiMod 
            listOfSMS[glob + 1]->open > listOfSMS[glob]->close) //gap up: 2nds open < 1sts close
            result = true;
        return result;
    }
};

// Recognize Peak
public ref class PeakRecognizer : public Recognizer {

public:

    PeakRecognizer() {}

    // adds middle index to index list if peak
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (isPeak(listOfSMS, glob)) {
            //indexList->Add(loc);
            indexList->Add(loc + 1);
            //indexList->Add(loc + 2);
        }
    }

    // adds middle index to index list if peak
    bool isPeak(List<SmartCandleStick^>^ listOfSMS, int glob) {
        bool result = false;
        if (glob >= listOfSMS->Count - 2)
            return false;
        else if (
            listOfSMS[glob + 1]->high > listOfSMS[glob]->high &&    //middle high > left high
            listOfSMS[glob + 1]->high > listOfSMS[glob + 2]->high)  //middle high > right high
            result = true;
        return result;
    }
};

// Recognize Vally
public ref class ValleyRecognizer : public Recognizer {

public:

    ValleyRecognizer() {}

    // adds middle index to index list if valley
    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
        if (isValley(listOfSMS, glob)) {
            //indexList->Add(loc);
            indexList->Add(loc + 1);
            //indexList->Add(loc + 2);
        }
    }

    // adds middles of index to index list of valley
    bool isValley(List<SmartCandleStick^>^ listOfSMS, int glob) {
        bool result = false;
        if (glob >= listOfSMS->Count - 2)
            return false;
        else if (
            listOfSMS[glob + 1]->low < listOfSMS[glob]->low &&    //middle low < left low
            listOfSMS[glob + 1]->low < listOfSMS[glob + 2]->low)  //middle low < right low
            result = true;
        return result;
    }
};

// Recognizer template

//// Recognize GGG
//public ref class GGGRecognizer : public Recognizer {
//
//public:
//
//    GGGRecognizer() {}
//
//    virtual void recognizePattern(List<SmartCandleStick^>^ listOfSMS, int glob, int loc) override {
//        if (listOfSMS[glob]->)
//            indexList->Add(loc);
//    }
//};