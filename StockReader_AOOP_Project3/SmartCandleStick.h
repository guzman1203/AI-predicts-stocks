#pragma once
#include "CandleStick.h"

// A candlestick class with more functionalities
public ref class SmartCandleStick : public CandleStick
{
public:
	// Variables to discern patterns
	static const double noBody_p = 0.05; //percent of range for the body to be considered none existant
	static const double noTail_p = 0.05; //percent of range for the tail to be none existant
	static const double doji_p = 0.40; //percent of tails length for doji
	static const double doji_dfgs_p = 0.80; //percent of tail length for dragon fly or gravestone doji
	static const double hammer_body_p = 0.25;
	static const double hammer_longT_p = 0.60;

public:
	//
	// Constructors
	//

	// Default
	SmartCandleStick() {}

	// Construct from string
	SmartCandleStick(System::String ^ input) : CandleStick(input) {
		//Compute higher level properties and patterns
		computeHigherLevelProps();
	}

	SmartCandleStick(CandleStick^ baseCS) {
		this->high = baseCS->high;
		this->low = baseCS->low;
		this->open = baseCS->open;
		this->close = baseCS->close;

		//Compute higher level properties and patterns
		computeHigherLevelProps();
	}

	// Construct from base
	SmartCandleStick(CandleStick cs) {
		open = cs.open;
		high = cs.high;
		low = cs.low;
		close = cs.close;

		//Compute higher level properties and patterns
		computeHigherLevelProps();
	}

public:
	// Property variables
	float range;
	float bodyRange;
	float topPrice;
	float bottomPrice;
	float upperT;
	float lowerT;
	// Pattern variables
	bool isBear;
	bool isBull;
	bool isNeu;
	bool isMaru;
	bool isBearMaru;
	bool isBullMaru;
	bool isDoj;
	bool isDragonFly;
	bool isGraveStone;
	bool isHamm;
	bool isInvertedHamm;
	//bool isEngulf;
	//bool isBearEngulf;
	//bool isBullEngulf;
	//bool isBearHami;
	//bool isBullHami;
	//bool isPea;
	//bool isVall;

private:
	// Pattern functions
	bool isNeutral();
	bool isBullish();
	bool isBearish();
	bool isMarubuzo();
	bool isBearishMarubuzo();
	bool isBullishMarubuzo();
	bool isDoji();
	bool isDoji_dragonfly();
	bool isDoji_gravestone();
	bool isHammer();
	bool isInvertedHammer();
	//bool isEngulfing();
	//bool isBearEngulfing();
	//bool isBullEngulfing();
	//bool isBearHamis();
	//bool isBullHamis();
	//bool isPeak();
	//bool isValley();

private:
	// Bundle computations
	void computeProperties();
	void computePatterns();
	void computeHigherLevelProps();
};


