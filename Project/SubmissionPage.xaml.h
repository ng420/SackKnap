//
// SubmissionPage.xaml.h
// Declaration of the SubmissionPage class
//

#pragma once

#include "SubmissionPage.g.h"

namespace Project
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SubmissionPage sealed
	{
	public:
		SubmissionPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		Platform::String^ S;
		void replay(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void menu(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void next(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
