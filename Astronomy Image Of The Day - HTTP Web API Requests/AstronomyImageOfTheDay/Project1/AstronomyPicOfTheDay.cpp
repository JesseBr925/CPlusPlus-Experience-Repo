//Written 03/2022
//By @JesseBr925 Github.com
//
//This application is an example application that is capable of opening a webpage to the NASA image of the day.
//It first asks the user whether or not it would like to view the image of the day.
//It then does so by first making an API call to NASA's web api to retrieve the URL, retrieves the image link.
//Then uses windows.h to execute a built in function to open a web browser to the given URL.

#include <iostream>
#include <windows.h>
#include "curl.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#pragma comment (lib, "Shell32")

int main(){

    std::cout << "Welcome," << "\n This is an application that gives the user the ability to create an API call to retrieve a link to the NASA astronomy image of the day.\n"; 
    std::cout << "It is worth noting to make this application work, you will need to retrieve your own free API key from NASA's api webpage: https://api.nasa.gov/";
    std::cout << "Follow the process as directed by the 'Getting Started' on the webpage, and a key will emailed to you.  Save the key, as it will be used as input in this program.\n";

    std::string APIKey = "YourApiKeyGoesHere";

    std::cout << "Please select one of the following options! OR ELSE!"; 
    std::cout << "A - Open NASAS Astronomic Image of the Day in default web browser.\n" ;
    std::cout << "X - Exit program\n";

    std::string userInput = "";
    
    while (userInput != "X"){
        std::cout << "Input: ";
        std::cin >> userInput;

        if (userInput == "A"){

            std::cout << "Place holder for future api call.";

        }
        else {
            return 0;
        }
    }
    return 0;
}

void openNASAImageOfTheDay(char url[]){
    char command[] = "open";
    ShellExecute(NULL, (LPCTSTR)command, (LPCTSTR)url, NULL, NULL, SW_SHOWNORMAL);
}

size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t new_length = size * nmemb;
    s->append((char*)contents, new_length);
    return new_length;
}

json post_request(const std::string& url, const std::string& post_fields) {
    CURL* curl;
    CURLcode res;
    std::string response_str;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {

        // Set the request URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Set the POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        // Set the callback function for handling response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        // Set the user data to be passed to the write_callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);

        // Perform the POST request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup after the request
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // Parse the response string into a JSON object and return it
    json response_json = json::parse(response_str);
    return response_json;
}