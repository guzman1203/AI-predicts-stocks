/*
Author:		William Gonzalez-Guzman
*/

#include <iostream>

#pragma once

// Stock ticker candlestick class
public ref class CandleStick
{
public:
    // Constant static candle stick properties
    static System::String^ referenceString = "\"Ticker\",\"Period\",\"Date\",\"Open\",\"High\",\"Low\",\"Close\",\"Volume\"";
    static array<System::String^>^ delimiters = gcnew array<System::String^>{ "\",", "\",\"", "\"" };

public:
    // Candle stick properties
    property System::String^ ticker;
    property System::String^ period;
    property System::DateTime date;
    property float open;
    property float high;
    property float low;
    property float close;
    property System::Int64 volume;

public:

    //
    // Constructors
    //

    // main constructor
    CandleStick(System::String^ input) {
        // input >> this->ticker >> this->period >> this->date >> this->open >> this->high >> this->close >> this->low >> this->volume;

        // Split the input sting into 3 values
        array<System::String^>^ values = input->Split(delimiters, System::StringSplitOptions::RemoveEmptyEntries);

        // Split the last element into 5
        array<System::String^>^ num_values = values[3]->Split(gcnew array<System::String^>{","}, System::StringSplitOptions::None);

        // Check if input string was split into 4 values and that the last element into 5
        if (values->Length != 4 && num_values->Length != 5) {
            throw gcnew System::ArgumentException("Invalid input format.");
        }

        // Input the data of the CandleStick Object
        ticker = values[0];                             //ticker
        period = values[1];                             //period
        date = System::DateTime::Parse(values[2]);      //date

        open = System::Single::Parse(num_values[0]);    //open 
        high = System::Single::Parse(num_values[1]);    //high
        low = System::Single::Parse(num_values[2]);     //low
        close = System::Single::Parse(num_values[3]);   //close
        volume = System::Int64::Parse(num_values[4]);   //volume    
    }
    // Default constructor
    CandleStick() {}

};

