#pragma once

/*
Author:		William Gonzalez-Guzman
*/

#include "Form_DisplayStock.h"
#include "CandleStick.h"
#include "SmartCandleStick.h"

namespace AOOP_Project_3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	using namespace System::IO;

#define ERR_NO_FILES "Error : No Files"
#define ERR_INVALID_DATE "Error : Invalid Date"


	/// <summary> A display window for a chart displaying a ticker's candlestick information.</summary>
	public ref class Form_Control : public System::Windows::Forms::Form
	{
		// List of all candlesticks that have been loaded
	private: System::Collections::Generic::Dictionary<String^, System::Collections::Generic::List<SmartCandleStick^>^>^ mapOfStocks
		= gcnew System::Collections::Generic::Dictionary<String^, System::Collections::Generic::List<SmartCandleStick^>^>();

	public:
		Form_Control(void)
		{
			//
			//Initialize Form
			//
			InitializeComponent();
			// 
			// Set openFileDialog_stockFolder InitialDirectory
			//
			System::String^ initialPath = "Stock Data";
			this->openFileDialog_folderOfStocks->InitialDirectory = System::IO::Directory::GetParent(
				System::IO::Directory::GetCurrentDirectory())->FullName + "\\" + initialPath;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_Control()
		{
			if (components)
			{
				delete components;
			}
		}
		// Button that opens the open file dialog and loads the stock files
	private: System::Windows::Forms::Label^ label_startDate;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_startDate;
	private: System::Windows::Forms::Label^ label_endDate;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_endDate;
	private: System::Windows::Forms::Button^ button_loadMultiStocks;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_folderOfStocks;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->button_loadMultiStocks = (gcnew System::Windows::Forms::Button());
			   this->openFileDialog_folderOfStocks = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->dateTimePicker_endDate = (gcnew System::Windows::Forms::DateTimePicker());
			   this->dateTimePicker_startDate = (gcnew System::Windows::Forms::DateTimePicker());
			   this->label_startDate = (gcnew System::Windows::Forms::Label());
			   this->label_endDate = (gcnew System::Windows::Forms::Label());
			   this->SuspendLayout();
			   // 
			   // button_loadMultiStocks
			   // 
			   this->button_loadMultiStocks->Location = System::Drawing::Point(15, 93);
			   this->button_loadMultiStocks->Name = L"button_loadMultiStocks";
			   this->button_loadMultiStocks->Size = System::Drawing::Size(210, 45);
			   this->button_loadMultiStocks->TabIndex = 9;
			   this->button_loadMultiStocks->Text = L"Load Files";
			   this->button_loadMultiStocks->UseVisualStyleBackColor = true;
			   this->button_loadMultiStocks->Click += gcnew System::EventHandler(this, &Form_Control::button_loadMultiStocks_click);
			   // 
			   // openFileDialog_folderOfStocks
			   // 
			   this->openFileDialog_folderOfStocks->Filter = L"All files | *.csv|Monthy|*-month.csv|Weekly|*-week.csv|Daily|*-day.csv";
			   this->openFileDialog_folderOfStocks->Multiselect = true;
			   this->openFileDialog_folderOfStocks->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_Control::openFileDialog_stockFolder_FileOk);
			   // 
			   // dateTimePicker_endDate
			   // 
			   this->dateTimePicker_endDate->Location = System::Drawing::Point(15, 67);
			   this->dateTimePicker_endDate->Name = L"dateTimePicker_endDate";
			   this->dateTimePicker_endDate->Size = System::Drawing::Size(210, 20);
			   this->dateTimePicker_endDate->TabIndex = 14;
			   this->dateTimePicker_endDate->Value = System::DateTime(2023, 10, 10, 9, 45, 15, 0);
			   // 
			   // dateTimePicker_startDate
			   // 
			   this->dateTimePicker_startDate->Location = System::Drawing::Point(15, 28);
			   this->dateTimePicker_startDate->Name = L"dateTimePicker_startDate";
			   this->dateTimePicker_startDate->Size = System::Drawing::Size(210, 20);
			   this->dateTimePicker_startDate->TabIndex = 15;
			   this->dateTimePicker_startDate->Value = System::DateTime(2019, 9, 3, 0, 0, 0, 0);
			   // 
			   // label_startDate
			   // 
			   this->label_startDate->AutoSize = true;
			   this->label_startDate->Location = System::Drawing::Point(90, 12);
			   this->label_startDate->Name = L"label_startDate";
			   this->label_startDate->Size = System::Drawing::Size(55, 13);
			   this->label_startDate->TabIndex = 16;
			   this->label_startDate->Text = L"Start Date";
			   // 
			   // label_endDate
			   // 
			   this->label_endDate->AutoSize = true;
			   this->label_endDate->Location = System::Drawing::Point(90, 51);
			   this->label_endDate->Name = L"label_endDate";
			   this->label_endDate->Size = System::Drawing::Size(52, 13);
			   this->label_endDate->TabIndex = 17;
			   this->label_endDate->Text = L"End Date";
			   // 
			   // Form_Control
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(240, 200);
			   this->Controls->Add(this->label_endDate);
			   this->Controls->Add(this->label_startDate);
			   this->Controls->Add(this->dateTimePicker_startDate);
			   this->Controls->Add(this->dateTimePicker_endDate);
			   this->Controls->Add(this->button_loadMultiStocks);
			   this->Name = L"Form_Control";
			   this->Text = L"Form_Control";
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	// Opens the file dialog to select stock files
	private: System::Void button_loadMultiStocks_click(System::Object^ sender, System::EventArgs^ e)
	{
		// Prompt Dialogbox and save result
		System::Windows::Forms::DialogResult op_result = openFileDialog_folderOfStocks->ShowDialog();
	}

	// Event handler for whe the file dialog returns OK. Will loads up a new display form for each stock file selected
	private: System::Void openFileDialog_stockFolder_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {

		//// Get the list of candlesticks from each file selected and store in the corresponding global variable
		//listOfListOfCandles = loadSelectedStockCandleSticks(openFileDialog_folderOfStocks->FileNames);

		// Get start and end date
		System::DateTime startDate = dateTimePicker_startDate->Value;
		System::DateTime endDate = dateTimePicker_endDate->Value;

		// List of stocks candlesticks
		List<SmartCandleStick^>^ listOfCandleSticks;

		// For every list of candles sticks in a list of lists
		for each (String ^ filePath in openFileDialog_folderOfStocks->FileNames) {
			// Get the new display form's title
			String^ formTitle = Path::GetFileNameWithoutExtension(filePath);

			// Get the start and end dates
			DateTime start = dateTimePicker_startDate->Value;
			DateTime end = dateTimePicker_endDate->Value;

			// Check if candle sticks have already been generated
			if (mapOfStocks->ContainsKey(formTitle))
				listOfCandleSticks = mapOfStocks[formTitle];
			else
			{
				// Generate the list of candlesticks within the file
				listOfCandleSticks = loadStockCandleSticksFromFile(filePath);
				listOfCandleSticks->Reverse(); //reverse the list

				// Store the stocks candlesticks
				mapOfStocks->Add(formTitle, listOfCandleSticks);
			}

			// Create a new display form for the candle stick list
			AOOP_Project_3::Form_DisplayStock^ newform = gcnew AOOP_Project_3::Form_DisplayStock(formTitle, start, end, listOfCandleSticks);

			// Display the form in a window
			newform->Show();
		}
	}

	// Loads multiple candle sticks lists from multiple appropriate files
	private: System::Collections::Generic::List<System::Collections::Generic::List<SmartCandleStick^>^>^ loadSelectedStockCandleSticks(array<System::String^>^ filePaths) {

		int fileAmount = filePaths->Length;
		System::Collections::Generic::List<System::Collections::Generic::List<SmartCandleStick^>^>^ listOfListOfCandlSticks = gcnew System::Collections::Generic::List<System::Collections::Generic::List<SmartCandleStick^>^>(fileAmount);

		// for each file
		for each (System::String ^ filePath in filePaths)
		{
			//convert file's contents into a list of candlesitcks
			System::Collections::Generic::List<SmartCandleStick^>^ listOfCandleSticks = loadStockCandleSticksFromFile(filePath);
			//add the list of candle sticks to the list of lists of candlesticks
			listOfListOfCandlSticks->Add(listOfCandleSticks);
		}
		listOfListOfCandlSticks->Reverse();

		return listOfListOfCandlSticks;
	}

    // Load candle sticks into a list from an appropriate file
	private: System::Collections::Generic::List<SmartCandleStick^>^ loadStockCandleSticksFromFile(String^ filePath) {

		List<SmartCandleStick^>^ listOfCandleSticks = gcnew List<SmartCandleStick^>(); //list of candlesitcks objs

		StreamReader^ reader = gcnew StreamReader(filePath); //streamReader to read file(s)
		String^ header = reader->ReadLine(); //read first line of the file

		// Check if we opened the correct type of file
		if (header == CandleStick::referenceString)
		{
			// Loop though file line by line till the end
			while (!reader->EndOfStream)
			{
				// Add the new CandleStick to the list of CandleSticks
				SmartCandleStick^ newCS = gcnew SmartCandleStick(reader->ReadLine());
				if (newCS != nullptr)
					listOfCandleSticks->Add(newCS);
				else
					exit(1);
			}
		}
		return listOfCandleSticks; //return list of candlestick objs
	}

	};
}
