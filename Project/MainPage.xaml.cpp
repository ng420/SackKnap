//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//
#pragma once
#include "pch.h"
#include "MainPage.xaml.h"
#include "Object.h"
#include "MenuPage.xaml.h"
#include <list>
#include <time.h>
#include "SubmissionPage.xaml.h"

const int MAX(32);
using namespace Project;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Popups;
using namespace Windows::Storage;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
	ObjGrp = ref new ObjectsGroup();
}
/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
	String^ L=ref new String;
	L = ((String^)e->Parameter);
	Level=ConvertToInt(L);
	Initialize();	
}
void MainPage::PageLoadedHandler(Platform::Object^ sender,
          Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
}
void MainPage::Initialize()
{
	//Level=12;
	localSettings = ApplicationData::Current->LocalSettings;
	auto HighestLevelReach = safe_cast<String^>(localSettings->Values->Lookup("HighestLevelReached"));
	if(localSettings->Values->HasKey("NumSubmit"))
		NumSubmit=safe_cast<IPropertyValue^>(localSettings->Values->Lookup("NumSubmit"))->GetInt32();
	else
		NumSubmit=0;
	//medals = safe_cast<Array<int>^>(localSettings->Values->Lookup("medals"));
	medals = ref new Array<int>(MAX);
	times = ref new Array<Platform::String^>(MAX);
	if(HighestLevelReach==nullptr) HighestLevelReached =1;
	else HighestLevelReached=ConvertToInt(HighestLevelReach);
	for(int i=0;i<HighestLevelReached;i++)
	{
		String^ temp= ref new String;
		String^ med=ref new String;
		temp="medal"+ConvertToPString(i);
		med = safe_cast<String^>(localSettings->Values->Lookup(temp));
		if(med!=nullptr)
		medals[i]=ConvertToInt(med);
		else
			medals[i]=-1;
		temp="time"+ConvertToPString(i);
		auto time=safe_cast<String^>(localSettings->Values->Lookup(temp));
		if(med!=nullptr)
			times[i]=(time);
		else
			times[i]="N/A";
	}
	LevelText->Text=ConvertToPString(Level);
	InitializeObjects();
	AnalyzeObjects();
	StartTimerAndRegisterHandler();
	this->DataContext = ObjGrp;
}
void MainPage::InitializeObjects()
{
		IsPaused=false;
		ObjGrp->Time="0:00";
		ObjGrp->Profit="0";
		ObjGrp->Weight="0";
		ObjectCreator(5+Level/2);
}
Platform::String^ Project::MainPage::conv(Platform::String^ S1, Platform::String^ S2)
{
	int a=0,b=0;
	Platform::String^ initial = S1;
	const wchar_t *W = initial->Data();
	int Size = wcslen( W );
	char *CString= new char[Size + 1];
	CString[ Size ] = 0;
	for(int y=0;y<Size; y++)
	{
		CString[y] = (char)W[y];
	}
	a+=atoi(CString);
	initial = S2;
	W = initial->Data();
	 Size = wcslen( W );
	CString= new char[Size + 1];
	CString[ Size ] = 0;
	for(int y=0;y<Size; y++)
	{
		CString[y] = (char)W[y];
	}
	b+=atoi(CString);
	int c=a+b;
	char char_str[10];
	_itoa_s(c,char_str,10);
	std::string s_str = std::string(char_str);
	std::wstring wid_str = std::wstring(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	Platform::String^ p_string = ref new Platform::String(w_char);
	return p_string;

}
void MainPage::ProfitEval(unsigned int i)
	{
		w+=ConvertToInt(ob->GetAt(i)->weight);
		p+=ConvertToInt(ob->GetAt(i)->profit);
		if(w<=ConvertToInt(ObjGrp->Capacity)) l.push_back(p);
		for(unsigned int j=i+1;j<ob->Size;j++)
		{
			if(w<=ConvertToInt(ObjGrp->Capacity))
			{
				ProfitEval(j);
				w-=ConvertToInt(ob->GetAt(j)->weight);
				p-=ConvertToInt(ob->GetAt(j)->profit);
			}
		}
	}
void MainPage::AnalyzeObjects()
	{
		w=0;p=0;
		int c;
		l.clear();
		ob = ref new Platform::Collections::Vector<Objects^>();
		for(unsigned int i=0;i<ObjGrp->Items->Size;i++)
			ob->Append(ObjGrp->Items->GetAt(i));

		c=ConvertToInt(ObjGrp->Capacity);
		for(unsigned int i=0;i<ob->Size;i++)
		{
			ProfitEval(i);w-=ConvertToInt(ob->GetAt(i)->weight);p-=ConvertToInt(ob->GetAt(i)->profit);
			//l.push_back(ConvertToInt(ob->GetAt(i)->profit));
		}
		l.sort();
		l.reverse();
		lit=l.begin();
		ObjGrp->Gold=ConvertToPString(*lit);
		int temp=*lit;
		while(temp==*lit && lit!=l.end())
			lit++;
		ObjGrp->Silver=ConvertToPString(*lit);
		temp=*lit;
		while(temp==*lit && lit!=l.end())
			lit++;
		ObjGrp->Bronze=ConvertToPString(*lit);
		temp=*lit;
		while(temp==*lit && lit!=l.end())
			lit++;
		ObjGrp->Minimum=ConvertToPString(*lit);
	Gold->Text=ObjGrp->Gold;
	Silver->Text=ObjGrp->Silver;
	Bronze->Text=ObjGrp->Bronze;
	Minimum->Text=ObjGrp->Minimum;
	int total_weight=0;
	for (unsigned int i=0;i<(ObjGrp->Items->Size);i++)
	{
		total_weight+=ConvertToInt(ObjGrp->Items->GetAt(i)->weight);
	}
	}
Platform::String^ MainPage::ConvertToPString(int val)
	{
		char char_str[10];
		_itoa_s(val,char_str,10);
		std::string s_str = std::string(char_str);
		std::wstring wid_str = std::wstring(s_str.begin(), s_str.end());
		const wchar_t* w_char = wid_str.c_str();
		Platform::String^ p_string = ref new Platform::String(w_char);
		return p_string;
	}
int MainPage::ConvertToInt(Platform::String^ initial)
{
	const wchar_t *W = initial->Data();
	int Size = wcslen( W );
	char *CString= new char[Size + 1];
	CString[ Size ] = 0;
	for(int y=0;y<Size; y++)
	{
		CString[y] = (char)W[y];
	}
		return atoi(CString);
}
void Project::MainPage::ItemView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	auto obj6 =ItemListView->SelectedItems;
	/*for (auto ob2: (ItemListView->SelectedItems))*/
	ObjGrp->Profit="0";
	ObjGrp->Weight="0";
	for(unsigned int i=0;i<(obj6->Size);i++)
	{
		auto ob=safe_cast<Objects^>(obj6->GetAt(i));
		ObjGrp->Profit=conv(ObjGrp->Profit,ob->profit);
		ObjGrp->Weight=conv(ObjGrp->Weight,ob->weight);
	}

	ProfitBlock->Text=ObjGrp->Profit;
	WeightBlock->Text=ObjGrp->Weight;
}


void Project::MainPage::Submit(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int profit = ConvertToInt(ProfitBlock->Text);
	int weight = ConvertToInt(WeightBlock->Text);
	int gold = ConvertToInt(Gold->Text);
	int silver = ConvertToInt(Silver->Text);
	int bronze = ConvertToInt(Bronze->Text);
	int minimum = ConvertToInt(Minimum->Text);
	int capacity = ConvertToInt(Capacity->Text);
	bool PassToNextLevel=false;
	Point P(10,10);
	Platform::String^ S;
	int med=-1;

	if (weight<=capacity)
	{
		if (profit>=gold)
		{
			S="Congrats! You got gold.";
			PassToNextLevel=true;
			med=3;
		}
		else if (profit>=silver)
		{
			PassToNextLevel=true;
			S="You got silver.";
			med=2;
		}
		else if (profit>=bronze)
		{
			PassToNextLevel=true;
			S="You got bronze.";
			med=1;
		}
		else if (profit>=minimum)
		{
			PassToNextLevel=true;
			S="You passed the level.";
			med=0;
		}
		else
		{
			S="You did not reach the Minimum Required Profit.Try Again.";
		}
	}
	else
	{
		S="Capacity exceeded! Try Again.";
	}
	auto flyout = ref new MessageDialog("",S);
	if(PassToNextLevel)
	{
		auto values = localSettings->Values;
		auto Time = Timer->Text;
		NumSubmit++;
		values->Insert("NumSubmit", dynamic_cast<PropertyValue^>(PropertyValue::CreateInt32(NumSubmit)));
		if(Level!=HighestLevelReached)
		{
			if(med>medals[Level-1])
			{
				medals[Level-1] = med;
				values->Insert("medal"+ConvertToPString(Level-1),dynamic_cast<PropertyValue^>(PropertyValue::CreateString(ConvertToPString(med))));
			}
			if(isTimeLesser(Time,times[Level-1]))
			{
				times[Level-1]=Time;
				values->Insert("time"+ConvertToPString(Level-1),dynamic_cast<PropertyValue^>(PropertyValue::CreateString(Time)));
			}
		}
		else
		{
			medals[Level-1] = med;
			times[Level-1]=Time;
			HighestLevelReached=Level+1;
			auto values = localSettings->Values;
			auto temp = "medal"+ConvertToPString(Level-1);
			values->Insert("HighestLevelReached", dynamic_cast<PropertyValue^>(PropertyValue::CreateString(ConvertToPString(HighestLevelReached))));
			values->Insert(temp, dynamic_cast<PropertyValue^>(PropertyValue::CreateString(ConvertToPString(med))));
			values->Insert("time"+ConvertToPString(Level-1),dynamic_cast<PropertyValue^>(PropertyValue::CreateString(Time)));
		}
		  flyout->Commands->Append(ref new UICommand("Try Again", ref new UICommandInvokedHandler([this](IUICommand^ command)
		{
			ObjGrp->Items->Clear();
			InitializeObjects();
			AnalyzeObjects();
			ItemListView->SelectedItems->Clear();
			//Initialize();
			
		})));
	  
		  flyout->Commands->Append(ref new UICommand("Continue", ref new UICommandInvokedHandler([this](IUICommand^ command)
		{
			//rootPage->NotifyUser("The 'Install updates' command has been selected.", NotifyType::StatusMessage);
			Level++;
			LevelText->Text=ConvertToPString(Level);
			ObjGrp->Items->Clear();
			InitializeObjects();
			AnalyzeObjects();
			ItemListView->SelectedItems->Clear();
		})));

		  flyout->DefaultCommandIndex = 1;
		// Set the command to be invoked when escape is pressed
		  flyout->CancelCommandIndex = 1;
		  ApplicationDataCompositeValue^ composite = ref new ApplicationDataCompositeValue();
			composite->Insert("level", dynamic_cast<PropertyValue^>(PropertyValue::CreateString(ConvertToPString(Level))));
			composite->Insert("levelnext", dynamic_cast<PropertyValue^>(PropertyValue::CreateString(ConvertToPString(Level+1))));
			composite->Insert("time", dynamic_cast<PropertyValue^>(PropertyValue::CreateString(Time)));
			composite->Insert("med", dynamic_cast<PropertyValue^>(PropertyValue::CreateString(S)));	
		values->Insert("CurrentLevelSetting", composite);
		CheckAchievements();
		if(Level<MAX+1)
		  this->Frame->Navigate(SubmissionPage::typeid,this);
		else
			;
	}
	else
	{
		 flyout->Commands->Append(ref new UICommand("Try Again", ref new UICommandInvokedHandler([this](IUICommand^ command)
		{
			IsPaused=false;
		})));
		 flyout->DefaultCommandIndex = 0;
		  flyout->CancelCommandIndex = 0;
		  IsPaused=true;
	flyout->ShowAsync();
	}
	
}
void Project::MainPage::StartTimerAndRegisterHandler()
{
	DispatcherTimer^ timer=ref new DispatcherTimer();
    TimeSpan ts;
    ts.Duration = 10000000;
    timer->Interval = ts;
    timer->Start();
	timer->Tick += ref new EventHandler<Object^>(this,&Project::MainPage::OnTick);
}
void Project::MainPage::OnTick(Object^ sender,Object^ e)
{   
	Platform::String^ time = ObjGrp->Time;
	const wchar_t* T = time->Data();
	char second[3],minute[3];
	int i;
	int Size = wcslen(T);
	char *CString= new char[Size + 1];
	for(i=0;i<Size;i++)
	{
		CString[i] = (char)T[i];
	}
	minute[0]=CString[0];
	for(i=2;i<Size;i++)
		second[i-2]=CString[i];
	int seconds=atoi(second);
	int minutes=atoi(minute);
	seconds += 1;
	if(seconds==60)
	{
		seconds=0;
		minutes+=1;
 	}
	char tim[3],tis[3];
	_itoa_s(minutes,tim,10);
	_itoa_s(seconds,tis,10);
	std::string m_str = std::string(tim);
	std::string s_str = std::string(tis);
	std::wstring widm_str = std::wstring(m_str.begin(), m_str.end());
	std::wstring wids_str = std::wstring(s_str.begin(), s_str.end());
	const wchar_t* wm_char = widm_str.c_str();
	const wchar_t* ws_char = wids_str.c_str();
	Platform::String^ m_string = ref new Platform::String(wm_char);
	Platform::String^ s_string = ref new Platform::String(ws_char);
	if(!IsPaused) 
		ObjGrp->Time=(seconds>=10)?(m_string+":"+s_string):(m_string+":0"+s_string);
	Timer->Text=ObjGrp->Time;
 }
void MainPage::ObjectCreator(int t)
{
			float curRatio;
			int wt,pt;
			bool isValid=false;
			srand((unsigned int)time(NULL));
			auto ratio = float((200+rand()%200)/(100.0));
			for(int i=0;i<t;i++)
			{   isValid=false;
				curRatio=((ratio*100)+rand()%200-100)/100;
				while(!isValid)
				{
					isValid=true;
					wt=10+rand()%20;
					for(int j=0;j<i;j++)
						if(wt==ConvertToInt(ObjGrp->Items->GetAt(j)->weight))
						isValid=false;
					pt=int(curRatio*(wt));
				}
				AddObject(ConvertToPString(pt),ConvertToPString(wt));
			}
			int c=0;
			for(int i=0;i<t;i++)
			c+=ConvertToInt(ObjGrp->Items->GetAt(i)->weight);
			c=(c/2);
			ObjGrp->Capacity=ConvertToPString(c);
			Capacity->Text=ObjGrp->Capacity;
}



void Project::MainPage::GoBack(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(MenuPage::typeid,this);
}

bool Project::MainPage::isTimeLesser(Platform::String^ Time1,Platform::String^ Time2)
{
	const wchar_t *W = Time1->Data();
	int Size = wcslen( W );
	char *CString= new char[Size + 1];
	CString[ Size ] = 0;
	for(int y=0;y<Size; y++)
	{
		CString[y] = (char)W[y];
	}
	W = Time2->Data();
	Size = wcslen( W );
	char *DString= new char[Size + 1];
	DString[ Size ] = 0;
	for(int y=0;y<Size; y++)
	{
		DString[y] = (char)W[y];
	}
	return (strcmp(CString,DString)<0);
}

void MainPage::CheckAchievements()
{
	bool isComplete(false),isAllGold(false),isOnSpree(false),isOnUSpree(false),isTimeSavvy(false),isTimeUSavvy(false),isUSubmitter(false);
	ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
	ApplicationDataCompositeValue^ composit = safe_cast<ApplicationDataCompositeValue^>(localSettings->Values->Lookup("Achievements"));
	int c(0);
	if (composit!=nullptr)
	{
		isComplete = safe_cast<IPropertyValue^>(composit->Lookup("isComplete"))->GetBoolean();
		isAllGold = safe_cast<IPropertyValue^>(composit->Lookup("isAllGold"))->GetBoolean();
		isOnSpree = safe_cast<IPropertyValue^>(composit->Lookup("isOnSpree"))->GetBoolean();
		isOnUSpree = safe_cast<IPropertyValue^>(composit->Lookup("isOnUSpree"))->GetBoolean();
		isTimeSavvy = safe_cast<IPropertyValue^>(composit->Lookup("isTimeSavvy"))->GetBoolean();
		isTimeUSavvy = safe_cast<IPropertyValue^>(composit->Lookup("isTimeUSavvy"))->GetBoolean();
		isUSubmitter = safe_cast<IPropertyValue^>(composit->Lookup("isUSubmitter"))->GetBoolean();
	}
	if(!isComplete)
		if(HighestLevelReached==MAX+1)
			isComplete=true;
	if(!isAllGold)
	{	
		for(auto medal:medals)
		{
			if(medal!=3)
				c++;
		}
		if(!c)
			isAllGold=true;
	}
	if(!isTimeSavvy)
	{
		c=0;
		for(int i=0;i<10;i++)
		{
			if(!isTimeLesser(times[i],"0:30"))
				c++;
		}
			if(!c)
				isTimeSavvy=true;
	}
	if(!isTimeUSavvy&&HighestLevelReached>=20)
	{
		c=0;
		for(int i=10;i<20;i++)
		{
			if(!isTimeLesser(times[i],"1:00"))
				c++;
		}
			if(!c)
				isTimeUSavvy=true;
		
	}
	if(!isUSubmitter)
		if(NumSubmit>=100)
			isUSubmitter=true;

	ApplicationDataCompositeValue^ composite = ref new ApplicationDataCompositeValue();
	composite->Insert("isComplete", dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(isComplete)));
	composite->Insert("isAllGold", dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(isAllGold)));
	composite->Insert("isTimeSavvy", dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(isTimeSavvy)));
	composite->Insert("isTimeUSavvy", dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(isTimeUSavvy)));
	composite->Insert("isOnSpree", dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(isOnSpree)));
	composite->Insert("isOnUSpree", dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(isOnUSpree)));
	composite->Insert("isUSubmitter", dynamic_cast<PropertyValue^>(PropertyValue::CreateBoolean(isUSubmitter)));
	auto values = ApplicationData::Current->LocalSettings->Values;
	values->Insert("Achievements", composite);
}