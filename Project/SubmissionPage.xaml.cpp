//
// SubmissionPage.xaml.cpp
// Implementation of the SubmissionPage class
//

#include "pch.h"
#include "SubmissionPage.xaml.h"
#include "MenuPage.xaml.h"

using namespace Project;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

SubmissionPage::SubmissionPage()
{
	InitializeComponent();
	
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void SubmissionPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	S = ((String^)e->Parameter);
	result->Text=S;
}


void Project::SubmissionPage::replay(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Project::SubmissionPage::menu(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(MenuPage::typeid);
}


void Project::SubmissionPage::next(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
