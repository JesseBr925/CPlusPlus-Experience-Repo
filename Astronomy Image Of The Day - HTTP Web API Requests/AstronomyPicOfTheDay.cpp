//Written 03/2022
//By @JesseBr925 Github.com
//
//This application is an example application that is capable of opening a webpage to the NASA image of the day.
//It first asks the user whether or not it would like to view the image of the day.
//It then does so by first making an API call to NASA's web api to retrieve the URL, retrieves the image link.
//Then uses windows.h to execute a built in function to open a web browser to the given URL.

#include <iostream>
#include <windows.h>

int main(){

    std::cout << "Welcome," << "\n This is an application that gives the user the ability to create an API call to retrieve a link to the NASA astronomy image of the day.\n"; 
    std::cout << "It is worth noting to make this application work, you will need to retrieve your own free API key from NASA's api webpage: https://api.nasa.gov/";
    std::cout << "Follow the process as directed by the 'Getting Started' on the webpage, and a key will emailed to you.  Save the key, as it will be used as input in this program.\n";

    std::string APIKey = "YourApiKeyGoesHere";

    std::cout << "Please select one of the following options! OR ELSE!"; 
    std::cout << "A - Open NASAS Astronomic Image of the Day in default web browser." ;
    std::cout << "X - Exit program";

    std::string userInput = "";
    
    while (userInput != "X"){
        std::cout << "Input: ";
        std::cin >> userInput;

        if (userInput == "A"){

            contactAPI();

        }
    }
    return 0;
}


char* contactAPI(){

}

void openNASAImageOfTheDay(char url[]){
    char command[] = "open";
    ShellExecute(NULL, (LPCTSTR)command, (LPCTSTR)url, NULL, NULL, SW_SHOWNORMAL);
}
