/*
Author:		William Gonzalez - Guzman
*/

#include "pch.h"
#include "SmartCandleStick.h"

// Neautral, Bearish, Bullish

//is this neutral (not bearish or bullish)
bool SmartCandleStick::isNeutral() { return ((bodyRange <= noBody_p * range) && (abs(upperT - lowerT) / range <= noTail_p)); }
//is this bullish
bool SmartCandleStick::isBullish() { return close > open && !isNeutral(); }
// is this bearish
bool SmartCandleStick::isBearish() { return close < open && !isNeutral(); }

// Marubuzo

// Determine if candlestick is a marubuzo (no tails, all body)
bool SmartCandleStick::isMarubuzo() { return (upperT <= noTail_p * range) && (lowerT <= noBody_p * range); }
// Determine if marubuzo and bearish
bool SmartCandleStick::isBearishMarubuzo() { return isBearish() && isMarubuzo(); }
// Determine if marubuzo and bullish
bool SmartCandleStick::isBullishMarubuzo() { return isBullish() && isMarubuzo(); }

// Doji

// Determine if doji
bool SmartCandleStick::isDoji() { return (bodyRange <= noBody_p * range) && (upperT >= doji_p * range) && (lowerT >= doji_p * range); }
// Determine if doji dragonfly
bool SmartCandleStick::isDoji_dragonfly() { return (lowerT >= doji_dfgs_p * range) && (bodyRange <= noBody_p * range); }
// Determine if doji gravestone
bool SmartCandleStick::isDoji_gravestone() { return (upperT >= doji_dfgs_p * range) && (bodyRange <= noBody_p * range); }

// Hammer


// Determine if hammer
bool SmartCandleStick::isHammer() { return (bodyRange >= hammer_body_p * range) && (lowerT >= hammer_longT_p * range); }
// Determine if inverted hammer
bool SmartCandleStick::isInvertedHammer() { return (bodyRange >= hammer_body_p * range) && (upperT >= hammer_longT_p * range); }
//
//// Engulfing
//
//// Determine if engulfing
//bool SmartCandleStick::isEngulfing() { return; }
//// Determine if bearish engulfing
//bool SmartCandleStick::isBearEngulfing() { return; }
//// Determine if bullish engulfing
//bool SmartCandleStick::isBullEngulfing() { return; }
//
//// Hamis
//
//// Determine if bearish hamis
//bool SmartCandleStick::isBearHamis() { return; }
//// Determine if bullish hamis
//bool SmartCandleStick::isBullHamis() { return; }
//
//// Peak and Valley
//
//// Determine if peak
//bool SmartCandleStick::isPeak() { return; }
//// Determine if valley
//bool SmartCandleStick::isValley() { return; }


//
// Compute properties and patterns
//

// Calculate properties of the candlestick
void SmartCandleStick::computeProperties() {
    range = high - low;
    bodyRange = abs(open - close);
    topPrice = (open > close) ? open : close;
    bottomPrice = (open < close) ? open : close;
    upperT = high - topPrice;
    lowerT = bottomPrice - low;
}
// Calculate patterns of the candlestick
void SmartCandleStick::computePatterns() {
    isNeu = isNeutral();
    isBear = isBearish();
    isBull = isBullish();
    isMaru = isMarubuzo();
    isBearMaru = isBearishMarubuzo();
    isBullMaru = isBullishMarubuzo();
    isBullMaru = isBullishMarubuzo();
    isDoj = isDoji();
    isDragonFly = isDoji_dragonfly();
    isGraveStone = isDoji_gravestone();
    isHamm = isHammer();
    isInvertedHamm = isInvertedHammer();

}
// Compute higher level properties and patterns
void SmartCandleStick::computeHigherLevelProps() {
    // Compute properties
    computeProperties();

    // Compute patterns
    computePatterns();

    // Compute higher level patterns
}