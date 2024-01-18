#pragma once

/*
Author:		William Gonzalez-Guzman
*/

#include "CandleStick.h"
#include "SmartCandleStick.h"
#include "Recognizer.h"

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

	// A display window for a chart displaying a ticker's candlestick information.
	public ref class Form_DisplayStock : public System::Windows::Forms::Form
	{
	// CandleStick list with all CandleStick objects in the selected files 
	public: List<SmartCandleStick^>^ allCandleSticksOfStock = gcnew List<SmartCandleStick^>();
	// CandleStick list with all CandleSticks we want 
	public: BindingList<SmartCandleStick^>^ displayList = gcnew BindingList<SmartCandleStick^>();

	public:
		Form_DisplayStock(String^ stockName, DateTime start, DateTime end, List<SmartCandleStick^>^ stocksCandleSticks)
		{
			// Check if start date < end date
			if (!isDatesValid(start, end))
				exit(1);

			// Initialize pattern color list
			InitializePatternColors();

			// Initialize pattern recognizer list
			InitializeRecognizers();

			// Initialize Form
			InitializeComponent();

			// Set openFileDialog_stockFolder InitialDirectory
			System::String^ initialPath = "Stock Data";
			this->openFileDialog_stockFolder->InitialDirectory = System::IO::Directory::GetParent(
				System::IO::Directory::GetCurrentDirectory())->FullName + "\\" + initialPath;
	
			// Set form's title
			changeFormTitleTo(stockName);
	
			// Set the start and end dates
			dateTimePicker_startDate->Value = start;
			dateTimePicker_endDate->Value = end;

			// Set stock candles sticks
			for each (SmartCandleStick^ candleStick in stocksCandleSticks)
				allCandleSticksOfStock->Add(candleStick);

			// Update display list
			updateDisplayList_viaDates();

			// Bind chart to display list
			bindChartToDisplayList();

			// Update chart display
			updateChart();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_DisplayStock()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: System::Windows::Forms::Button^ button_updateDates;
	private: System::Windows::Forms::Button^ button_clearPatterns;
	private: System::Windows::Forms::ComboBox^ comboBox_patternSelect;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_candleStickChart;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_endDate;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_startDate;
	private: System::Windows::Forms::Label^ label_displayform_tickername;
	private: System::Windows::Forms::Label^ label_patternSelect_1;
	private: System::Windows::Forms::Label^ label_startDate;
	private: System::Windows::Forms::Label^ label_endDate;
	private: System::Windows::Forms::Label^ label_patternSelect_2;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_stockFolder;
	
	private: System::ComponentModel::IContainer^ components;

	private: 
		// List of pattern colors in pattern selection position
		List<Color>^ patternColors = gcnew List<Color>();
		System::Void InitializePatternColors()
		{
			patternColors->Add(Color::Black);			// 0 All
			patternColors->Add(Color::Red);				// 1 Bearish
			patternColors->Add(Color::Cyan);			// 2 Bullish 
			patternColors->Add(Color::Gray);			// 3 Neutral
			patternColors->Add(Color::Blue);			// 4 Marubuzo
			patternColors->Add(Color::DarkBlue);		// 5 Bearish Marubuzo
			patternColors->Add(Color::BlueViolet);		// 6 Bullish Marubuzo
			patternColors->Add(Color::YellowGreen);		// 7 Doji 
			patternColors->Add(Color::DarkOliveGreen);	// 8 Gravestone Doji
			patternColors->Add(Color::SpringGreen);		// 9 Dragonfly Doji 
			patternColors->Add(Color::Orange);			//10 Hammer
			patternColors->Add(Color::PaleVioletRed);	//11 Inverted Hammer
			patternColors->Add(Color::MediumPurple);	//12 Engulfing
			patternColors->Add(Color::Indigo);			//13 Bearish Engulfing
			patternColors->Add(Color::MediumOrchid);	//14 Bullish Engulfing
			patternColors->Add(Color::SteelBlue);		//15 Bearish Harami
			patternColors->Add(Color::LightSteelBlue);  //16 Bullish Harami
			patternColors->Add(Color::Gold);			//17 Peak
			patternColors->Add(Color::DarkViolet);		//18 Valley
		}

	private:
		// List of recognizers in pattern selection position
		List<Recognizer^>^ patternRecs = gcnew List<Recognizer^>();
		System::Void InitializeRecognizers()
		{
			//patternRecs->Add(nullptr);			// 0 All
			patternRecs->Add(gcnew BearishRecognizer());			// 1 Bearish
			patternRecs->Add(gcnew BullishRecognizer());			// 2 Bullish 
			patternRecs->Add(gcnew NeutralRecognizer());			// 3 Neutral
			patternRecs->Add(gcnew MarubuzoRecognizer());			// 4 Marubuzo
			patternRecs->Add(gcnew BearishMarubuzoRecognizer());	// 5 Bearish Marubuzo
			patternRecs->Add(gcnew BullishMarubuzoRecognizer());	// 6 Bullish Marubuzo
			patternRecs->Add(gcnew DojiRecognizer());				// 7 Doji 
			patternRecs->Add(gcnew GravestoneDojiRecognizer());		// 8 Gravestone Doji
			patternRecs->Add(gcnew DragonflyDojiRecognizer());		// 9 Dragonfly Doji 
			patternRecs->Add(gcnew HammerRecognizer());				//10 Hammer
			patternRecs->Add(gcnew InvertedHammerRecognizer());		//11 Inverted Hammer
			patternRecs->Add(gcnew EngulfingRecognizer());			//12 Engulfing
			patternRecs->Add(gcnew BearishEngulfingRecognizer());	//13 Bearish Engulfing
			patternRecs->Add(gcnew BullishEngulfingRecognizer());	//14 Bullish Engulfing
			patternRecs->Add(gcnew BearishHaramiRecognizer());		//15 Bearish Harami
			patternRecs->Add(gcnew BullishHaramiRecognizer());		//16 Bullish Harami
			patternRecs->Add(gcnew PeakRecognizer());				//17 Peak
			patternRecs->Add(gcnew ValleyRecognizer());				//18 Valley
		}

		// NOTE FOR AFTER NAP : Change Recs to input with a list and change all CS to SMS

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->openFileDialog_stockFolder = (gcnew System::Windows::Forms::OpenFileDialog());
			this->chart_candleStickChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->dateTimePicker_endDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_startDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->label_startDate = (gcnew System::Windows::Forms::Label());
			this->label_endDate = (gcnew System::Windows::Forms::Label());
			this->button_updateDates = (gcnew System::Windows::Forms::Button());
			this->comboBox_patternSelect = (gcnew System::Windows::Forms::ComboBox());
			this->label_displayform_tickername = (gcnew System::Windows::Forms::Label());
			this->label_patternSelect_1 = (gcnew System::Windows::Forms::Label());
			this->label_patternSelect_2 = (gcnew System::Windows::Forms::Label());
			this->button_clearPatterns = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candleStickChart))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog_stockFolder
			// 
			this->openFileDialog_stockFolder->Filter = L"All files | *.csv|Monthy|*-month.csv|Weekly|*-week.csv|Daily|*-day.csv";
			this->openFileDialog_stockFolder->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_DisplayStock::openFileDialog_stockFolder_FileOk);
			// 
			// chart_candleStickChart
			// 
			chartArea1->AlignWithChartArea = L"ChartArea_Volume";
			chartArea1->Name = L"ChartArea_OHCL";
			chartArea2->AlignWithChartArea = L"ChartArea_OHCL";
			chartArea2->Name = L"ChartArea_Volume";
			this->chart_candleStickChart->ChartAreas->Add(chartArea1);
			this->chart_candleStickChart->ChartAreas->Add(chartArea2);
			legend1->Name = L"Legend1";
			this->chart_candleStickChart->Legends->Add(legend1);
			this->chart_candleStickChart->Location = System::Drawing::Point(0, 70);
			this->chart_candleStickChart->Name = L"chart_candleStickChart";
			series1->ChartArea = L"ChartArea_OHCL";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series1->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Lime";
			series1->IsXValueIndexed = true;
			series1->Legend = L"Legend1";
			series1->Name = L"OHCL";
			series1->XValueMember = L"date";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			series1->YValueMembers = L"high,low,open,close";
			series1->YValuesPerPoint = 4;
			series2->ChartArea = L"ChartArea_Volume";
			series2->Legend = L"Legend1";
			series2->Name = L"Volume";
			series2->XValueMember = L"date";
			series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series2->YValueMembers = L"volume";
			this->chart_candleStickChart->Series->Add(series1);
			this->chart_candleStickChart->Series->Add(series2);
			this->chart_candleStickChart->Size = System::Drawing::Size(1100, 460);
			this->chart_candleStickChart->TabIndex = 13;
			this->chart_candleStickChart->Text = L"chart_candleStickChart";
			// 
			// dateTimePicker_endDate
			// 
			this->dateTimePicker_endDate->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 8));
			this->dateTimePicker_endDate->Location = System::Drawing::Point(880, 570);
			this->dateTimePicker_endDate->Name = L"dateTimePicker_endDate";
			this->dateTimePicker_endDate->Size = System::Drawing::Size(400, 22);
			this->dateTimePicker_endDate->TabIndex = 14;
			this->dateTimePicker_endDate->Value = System::DateTime(2023, 10, 10, 9, 45, 15, 0);
			// 
			// dateTimePicker_startDate
			// 
			this->dateTimePicker_startDate->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker_startDate->Location = System::Drawing::Point(15, 570);
			this->dateTimePicker_startDate->Name = L"dateTimePicker_startDate";
			this->dateTimePicker_startDate->Size = System::Drawing::Size(400, 22);
			this->dateTimePicker_startDate->TabIndex = 15;
			this->dateTimePicker_startDate->Value = System::DateTime(2001, 9, 3, 0, 0, 0, 0);
			// 
			// label_startDate
			// 
			this->label_startDate->AutoSize = true;
			this->label_startDate->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_startDate->Location = System::Drawing::Point(132, 547);
			this->label_startDate->Name = L"label_startDate";
			this->label_startDate->Size = System::Drawing::Size(150, 16);
			this->label_startDate->TabIndex = 16;
			this->label_startDate->Text = L"Start Date";
			// 
			// label_endDate
			// 
			this->label_endDate->AutoSize = true;
			this->label_endDate->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_endDate->Location = System::Drawing::Point(1021, 547);
			this->label_endDate->Name = L"label_endDate";
			this->label_endDate->Size = System::Drawing::Size(115, 16);
			this->label_endDate->TabIndex = 17;
			this->label_endDate->Text = L"End Date";
			// 
			// button_updateDates
			// 
			this->button_updateDates->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 12));
			this->button_updateDates->Location = System::Drawing::Point(513, 538);
			this->button_updateDates->Name = L"button_updateDates";
			this->button_updateDates->Size = System::Drawing::Size(260, 50);
			this->button_updateDates->TabIndex = 18;
			this->button_updateDates->Text = L"Update Dates";
			this->button_updateDates->UseVisualStyleBackColor = true;
			this->button_updateDates->Click += gcnew System::EventHandler(this, &Form_DisplayStock::buttonUpdate_click);
			// 
			// comboBox_patternSelect
			// 
			this->comboBox_patternSelect->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->comboBox_patternSelect->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->comboBox_patternSelect->Font = (gcnew System::Drawing::Font(L"Goudy Old Style", 14));
			this->comboBox_patternSelect->FormattingEnabled = true;
			this->comboBox_patternSelect->Items->AddRange(gcnew cli::array< System::Object^  >(19) {
				L"All", L"Bearish", L"Bullish", L"Neutral",
					L"Marubuzo", L"Bearish Marubuzo", L"Bullish Marubuzo", L"Doji", L"Doji Gravestone", L"Doji Dragonfly", L"Hammer", L"Hammer Inverted",
					L"Engulfing", L"Bearish Engulfing", L"Bullish Engulfing", L"Bearish Harami", L"Bullish Harami", L"Peak", L"Valley"
			});
			this->comboBox_patternSelect->Location = System::Drawing::Point(1121, 149);
			this->comboBox_patternSelect->Name = L"comboBox_patternSelect";
			this->comboBox_patternSelect->Size = System::Drawing::Size(171, 31);
			this->comboBox_patternSelect->TabIndex = 20;
			this->comboBox_patternSelect->Text = L"All";
			this->comboBox_patternSelect->DrawItem += gcnew System::Windows::Forms::DrawItemEventHandler(this, &Form_DisplayStock::comboBox_patternSelect_PaintCombobox);
			this->comboBox_patternSelect->SelectedValueChanged += gcnew System::EventHandler(this, &Form_DisplayStock::comboBox_patternSelect_SelectedValueChanged);
			// 
			// label_displayform_tickername
			// 
			this->label_displayform_tickername->AutoSize = true;
			this->label_displayform_tickername->Font = (gcnew System::Drawing::Font(L"Goudy Old Style", 36, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label_displayform_tickername->Location = System::Drawing::Point(12, 9);
			this->label_displayform_tickername->Name = L"label_displayform_tickername";
			this->label_displayform_tickername->Size = System::Drawing::Size(593, 55);
			this->label_displayform_tickername->TabIndex = 21;
			this->label_displayform_tickername->Text = L"label_displayform_tickername";
			// 
			// label_patternSelect_1
			// 
			this->label_patternSelect_1->AutoSize = true;
			this->label_patternSelect_1->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_patternSelect_1->Location = System::Drawing::Point(1150, 109);
			this->label_patternSelect_1->Name = L"label_patternSelect_1";
			this->label_patternSelect_1->Size = System::Drawing::Size(113, 16);
			this->label_patternSelect_1->TabIndex = 22;
			this->label_patternSelect_1->Text = L"Pattern";
			// 
			// label_patternSelect_2
			// 
			this->label_patternSelect_2->AutoSize = true;
			this->label_patternSelect_2->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_patternSelect_2->Location = System::Drawing::Point(1162, 125);
			this->label_patternSelect_2->Name = L"label_patternSelect_2";
			this->label_patternSelect_2->Size = System::Drawing::Size(89, 16);
			this->label_patternSelect_2->TabIndex = 23;
			this->label_patternSelect_2->Text = L"Select";
			// 
			// button_clearPatterns
			// 
			this->button_clearPatterns->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 11));
			this->button_clearPatterns->Location = System::Drawing::Point(1121, 205);
			this->button_clearPatterns->Name = L"button_clearPatterns";
			this->button_clearPatterns->Size = System::Drawing::Size(171, 67);
			this->button_clearPatterns->TabIndex = 24;
			this->button_clearPatterns->Text = L"Clear Patterns";
			this->button_clearPatterns->UseVisualStyleBackColor = true;
			this->button_clearPatterns->Click += gcnew System::EventHandler(this, &Form_DisplayStock::button_clearPatterns_click);
			// 
			// Form_DisplayStock
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1300, 600);
			this->Controls->Add(this->button_clearPatterns);
			this->Controls->Add(this->label_patternSelect_2);
			this->Controls->Add(this->label_patternSelect_1);
			this->Controls->Add(this->label_displayform_tickername);
			this->Controls->Add(this->comboBox_patternSelect);
			this->Controls->Add(this->button_updateDates);
			this->Controls->Add(this->label_endDate);
			this->Controls->Add(this->label_startDate);
			this->Controls->Add(this->dateTimePicker_startDate);
			this->Controls->Add(this->dateTimePicker_endDate);
			this->Controls->Add(this->chart_candleStickChart);
			this->Name = L"Form_DisplayStock";
			this->Text = L"Display Stock Form";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candleStickChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	// Check for valid dates
	private: bool isDatesValid(DateTime start, DateTime end)
	{
		if (System::DateTime::Compare(start, end) > 0)
		{
			System::Windows::Forms::MessageBox::Show("Error: Endate earlier than start date.");
			return false;
		}
		else
			return true;
	}

	// File dialog returns OK, hence load selected stock file
	private: System::Void openFileDialog_stockFolder_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		// Array holding all file paths strings
		array<System::String^>^ filePaths = openFileDialog_stockFolder->FileNames;

		// Check if there are files
		if (filePaths->Length == 0) {
			// Exit with an error message
			MessageBox::Show(ERR_NO_FILES);
			exit(1);
		}

		// Loop through each file
		for each (System::String ^ file in filePaths) {

			StreamReader^ reader = gcnew StreamReader(file); //streamReader to read file(s)
			String^ header = reader->ReadLine(); //read first line of the file

			// Check if we opened the correct type of file
			if (header == CandleStick::referenceString)
			{
				// Loop though file line by line till the end
				while (!reader->EndOfStream)
				{
					// Add the new CandleStick to the stock list
					allCandleSticksOfStock->Add(gcnew SmartCandleStick(reader->ReadLine()));
				}
			}
		}
	}

	// Update the chart based on the current loaded stock. Used for when dates are changed.
	private: System::Void buttonUpdate_click(System::Object^ sender, System::EventArgs^ e) {
		// Updates the chart and graph based on the dates selected
		updateDisplayList_viaDates();

		// Bind data
		bindChartToDisplayList();

		// Update chart
		updateChart();
	}

	// Updates the display list with candlesticks within the start and end date range.
	private: System::Void updateDisplayList_viaDates()
	{
		// Get the current start and end dates
		DateTime startDate = dateTimePicker_startDate->Value;
		DateTime endDate = dateTimePicker_endDate->Value;

		// Clear the interest list
		displayList->Clear();

		// Clear pattern recognizers index lists
		clearRecsIndexList();

		// Check if start date < end date
		if (DateTime::Compare(startDate, endDate) > 0)
		{
			MessageBox::Show(ERR_INVALID_DATE);
		}
		else
		{
			int full_index = 0; //stock cs index counter
			int disp_index = 0; //display cs index counter
			for each (SmartCandleStick^ stick in allCandleSticksOfStock) {
				DateTime date = stick->date; //date of the candle stick
				// Check if candlestick date is within the start and end dates
				if (DateTime::Compare(startDate, date) <= 0 && DateTime::Compare(date, endDate) <= 0)
				{
					displayList->Add(stick); //add stick to interest list
					addToRecList(allCandleSticksOfStock, full_index, disp_index); //add to the pattern recognizers that match
					disp_index++;
				}
				// Check if we have past the end date (we assume the candle stick list is sorted)
				else if (DateTime::Compare(date, endDate) > 0)
				{
					break;
				}
				full_index++;
			}
		}
	}
	
	// Check each recoginzer in the recognizer list to see if candle stick at globIndex matches any and adds locIndex to recognizer's index list
	private: Void addToRecList(List<SmartCandleStick^>^ listOfSMS, int globIndex, int locIndex) {
	   patternRecs[0]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bearish
	   patternRecs[1]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bullish
	   patternRecs[2]->recognizePattern(listOfSMS, globIndex, locIndex);	//Neutral
	   patternRecs[3]->recognizePattern(listOfSMS, globIndex, locIndex);	//Marubuzo
	   patternRecs[4]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bearish Marubuzo
	   patternRecs[5]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bullish Marubuzo
	   patternRecs[6]->recognizePattern(listOfSMS, globIndex, locIndex);	//Doji
	   patternRecs[7]->recognizePattern(listOfSMS, globIndex, locIndex);	//Gravestone Doji
	   patternRecs[8]->recognizePattern(listOfSMS, globIndex, locIndex);	//Dragonfly Doji
	   patternRecs[9]->recognizePattern(listOfSMS, globIndex, locIndex);	//Hammer
	   patternRecs[10]->recognizePattern(listOfSMS, globIndex, locIndex);	//Inverted Hammer
	   patternRecs[11]->recognizePattern(listOfSMS, globIndex, locIndex);	//Engulfing
	   patternRecs[12]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bearish Engulfing
	   patternRecs[13]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bullish Engulfing
	   patternRecs[14]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bearish Harami
	   patternRecs[15]->recognizePattern(listOfSMS, globIndex, locIndex);	//Bullish Harami
	   patternRecs[16]->recognizePattern(listOfSMS, globIndex, locIndex);	//Peak
	   patternRecs[17]->recognizePattern(listOfSMS, globIndex, locIndex);	//Valley
   }
	// clears the index lists of each recognizer in the recognizer list
	private: Void clearRecsIndexList()
	{
		for each (Recognizer ^ r in patternRecs)
		{
			r->indexList->Clear();
		}
	}
	
	// Bind the charts with the current data.
	private: System::Void bindChartToDisplayList()
	{
		// Chart bind
		chart_candleStickChart->DataSource = displayList;
		chart_candleStickChart->DataBind();
	}

	// Update chart
	private: System::Void updateChart()
	{
		// Chart Update data
		chart_candleStickChart->Update();
	}

	// Resize chart (unused)
	private: System::Void autoSizeChart()
	{
		// Keep the range of the chart
		//for each (ChartArea^ chartArea in chart_candleStickChart->ChartAreas) {
		//	chartArea->AxisX->Minimum = dateTimePicker_startDate->Value.Date.ToOADate();
		//	chartArea->AxisX->Maximum = dateTimePicker_endDate->Value.Date.ToOADate();
		//}

		//ChartArea^ b = chart_candleStickChart->ChartAreas->FindByName("ChartArea_OHCL");
		//Series^ c = chart_candleStickChart->Series->FindByName("OHCL");

		for each (ChartArea^ OHCLArea in chart_candleStickChart->ChartAreas)
		{
			int minHeight = INT_MAX;
			int maxHeight = 0;
			for each (SmartCandleStick ^ candle in displayList)
			{
				if (minHeight > candle->low)
					minHeight = (int)candle->low;
				if (maxHeight < candle->high)
					maxHeight = (int)candle->high;
			}
			OHCLArea->AxisY->Maximum = maxHeight + 10;
			OHCLArea->AxisY->Minimum = minHeight - 10;
			break;
		}
	}
	
	// Update the form's title to match the stock its displaying.
	private: System::Void changeFormTitleTo(String^ newTitle)
	{
		// Variables for centering the title
		int totalLength;
		int labelSize;
		
		// Change title label to the new title
		label_displayform_tickername->Text = newTitle;
		
		// Center the new title
		totalLength = this->ClientSize.Width;
		labelSize = label_displayform_tickername->Size.Width;
		int newX = (totalLength / 2) - (labelSize / 2);
		label_displayform_tickername->Location = System::Drawing::Point(newX, label_displayform_tickername->Location.Y);
	}

	// Display an annotation at each data point that follows the selected pattern
	public: System::Void comboBox_patternSelect_SelectedValueChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ pattern; //stores selected pattern
		
		// Check that selected pattern is not null
		if (comboBox_patternSelect->SelectedItem != nullptr)
			pattern = comboBox_patternSelect->SelectedItem->ToString(); //store pattern

		// Do nothing if pattern is "None"
		if (pattern == "None")
			return;

		// List of patterns
		//List<String^>^ patternList = gcnew List<String^>();
		//for each (ComboBox::ObjectCollection ^ pattern in comboBox_patternSelect->Items)
		//	patternList->Add(pattern->ToString());

		// Check if there are data points in the series
		if (displayList->Count > 0)
		{
			// When a pattern is selected, draw up the annotations for each index is the corresponding recognizer's index list
			if (pattern == "Bearish") {
				anchorAnnotations(patternRecs[1 - 1], patternColors[1]);
			}
			else if (pattern == "Bullish") {
				anchorAnnotations(patternRecs[2 - 1], patternColors[2]);
			}
			else if (pattern == "Neutral") {
				anchorAnnotations(patternRecs[3 - 1], patternColors[3]);
			}
			else if (pattern == "Marubuzo") {
				anchorAnnotations(patternRecs[4 - 1], patternColors[4]);
			}
			else if (pattern == "Bearish Marubuzo") {
				anchorAnnotations(patternRecs[5 - 1], patternColors[5]);
			}
			else if (pattern == "Bullish Marubuzo") {
				anchorAnnotations(patternRecs[6 - 1], patternColors[6]);
			}
			else if (pattern == "Doji") {
				anchorAnnotations(patternRecs[7 - 1], patternColors[7]);
			}
			else if (pattern == "Doji Gravestone") {
				anchorAnnotations(patternRecs[8 - 1], patternColors[8]);
			}
			else if (pattern == "Doji Dragonfly") {
				anchorAnnotations(patternRecs[9 - 1], patternColors[9]);
			}
			else if (pattern == "Hammer") {
				anchorAnnotations(patternRecs[10 - 1], patternColors[10]);
			}
			else if (pattern == "Hammer Inverted") {
				anchorAnnotations(patternRecs[11 - 1], patternColors[11]);
			}
			else if (pattern == "Engulfing") {
				anchorAnnotations(patternRecs[12 - 1], patternColors[12]);
			}
			else if (pattern == "Bearish Engulfing") {
				anchorAnnotations(patternRecs[13 - 1], patternColors[13]);
			}
			else if (pattern == "Bullish Engulfing") {
				anchorAnnotations(patternRecs[14 - 1], patternColors[14]);
			}
			else if (pattern == "Bearish Harami") {
				anchorAnnotations(patternRecs[15 - 1], patternColors[15]);
			}
			else if (pattern == "Bullish Harami") {
				anchorAnnotations(patternRecs[16 - 1], patternColors[16]);
			}
			else if (pattern == "Peak") {
				anchorAnnotations(patternRecs[17 - 1], patternColors[17]);
			}
			else if (pattern == "Valley") {
				anchorAnnotations(patternRecs[18 - 1], patternColors[18]);
			}
		}
	}

	// Anchor annotations to display list's points based on the index list of the recognizer 
	private: void anchorAnnotations(Recognizer^ rec, Color clr) {
		
		// Get data points of the series
		DataPointCollection^ ohcl = chart_candleStickChart->Series->FindByName("OHCL")->Points;

		// Annotation line width
		double width = 1 / (double)ohcl->Count;

		if (displayList->Count > 0) 
		{
			for each (int i in rec->indexList) 
			{
				// Anchor an annotation at each datapoint that matches the single pattern
				RectangleAnnotation^ annotation = gcnew RectangleAnnotation();
				annotation->AxisX = chart_candleStickChart->ChartAreas[0]->AxisX; // X-axis
				annotation->AxisY = chart_candleStickChart->ChartAreas[0]->AxisY; // Y-axis

				// Set dimensions of annotation
				annotation->LineWidth = 1;
				annotation->Width = width;
				annotation->Height = 36.5;
				annotation->Y = chart_candleStickChart->ChartAreas[0]->AxisY->Maximum;

				// Set color
				annotation->LineColor = clr;
				annotation->BackColor = clr;

				// Anchor to data point
				annotation->AnchorDataPoint = ohcl[i];

				// Add the annotation to the chart
				chart_candleStickChart->Annotations->Add(annotation);
			}
		}
	}

	// Color the comboBox_patternSelect items's text to match the annotations
	private: System::Void comboBox_patternSelect_PaintCombobox(System::Object^ sender, DrawItemEventArgs^ e) {
		// Check if index is out of bounds
		if (e->Index < 0) {
			return;
		}
		// Get the ComboBox
		ComboBox^ comboBox = (ComboBox^)sender;

		// Get the item text
		String^ itemText = comboBox->Items[e->Index]->ToString();

		Color textColor; //text color variable

		// Set the color based on the item index
		if (e->Index == 0) //All
			textColor = patternColors[0];
		else if (e->Index == 1)				//Bearish
			textColor = patternColors[1];
		else if (e->Index == 2)				//Bullish
			textColor = patternColors[2];
		else if (e->Index == 3)				//Neutral
			textColor = patternColors[3];
		else if (e->Index == 4)				//Marubuzo
			textColor = patternColors[4];
		else if (e->Index == 5)				//Bearish Marubuzo
			textColor = patternColors[5];
		else if (e->Index == 6)				//Bullish Marubuzo
			textColor = patternColors[6];
		else if (e->Index == 7)				//Doji
			textColor = patternColors[7];
		else if (e->Index == 8)				//Gravestone Doji
			textColor = patternColors[8];
		else if (e->Index == 9)				//Dragonfly Doji
			textColor = patternColors[9];
		else if (e->Index == 10)			//Hammer
			textColor = patternColors[10];
		else if (e->Index == 11)			//Inverted Hammer
			textColor = patternColors[11];
		else if (e->Index == 12)			//Engulfing
			textColor = patternColors[12];
		else if (e->Index == 13)			//Bearish Engulfing
			textColor = patternColors[13];
		else if (e->Index == 14)			//Bullish Engulfing
			textColor = patternColors[14];
		else if (e->Index == 15)			//Bearish Harami
			textColor = patternColors[15];
		else if (e->Index == 16)			//Bullish Harami
			textColor = patternColors[16];
		else if (e->Index == 17)			//Peak
			textColor = patternColors[17];
		else if (e->Index == 18)			//Valley
			textColor = patternColors[18];

		// Create a brush for the text color
		Brush^ textBrush = gcnew SolidBrush(textColor);

		// Clear the item's background
		e->Graphics->FillRectangle(gcnew SolidBrush(SystemColors::Window), e->Bounds);

		// Draw the item text with the custom color
		e->Graphics->DrawString(itemText, e->Font, textBrush, e->Bounds, StringFormat::GenericDefault);

		// Clean up the brush
		delete textBrush;
	}

	// Clear the annotations on the chart
	private: System::Void button_clearPatterns_click(System::Object^ sender, System::EventArgs^ e) {
		chart_candleStickChart->Annotations->Clear();
	}
};
}
