#include<iostream>
#include <unistd.h>
#include <conio.h>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;

// Define a function to split a string based on a delimiter
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens; //store each data from the line
    string token; 
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

class ETE {
protected:
    string ete_staff_details = "ETE_Staff.csv";
    string ete_map = "ETE_Map.csv";

public:
    int no_of_faculty_ETE = 0;
    ETE() {
        
        countFaculty();
        initializeMap();
    }

    void countFaculty() {
        ifstream ifs(ete_staff_details);
        if (!ifs.is_open()) {
            cerr << "ERROR: Opening file " << ete_staff_details << endl;
            return;
        }

        string line;
        while (getline(ifs, line)) {
            no_of_faculty_ETE++;
        }

        ifs.close();
    }

    void initializeMap() 
    {

        ifstream details_file(ete_staff_details);
        ofstream map_file(ete_map);

        if (!details_file.is_open() || !map_file.is_open()) {
            cerr << "ERROR: Opening file " << ete_staff_details << " or " << ete_map << endl;
            return;
        }

        string line;
        while (getline(details_file, line)) {
            map_file << line << ",0" << endl; 
        }

        details_file.close();
        map_file.close();
    }
};

class ECE{
    protected:
        string ece_staff_details="ECE_Staff.csv";
        string ece_map= "ECE_Map.csv";
        
    public:
        int no_of_faculty_ECE=0;
        ECE() {
            
            countFaculty();
            initializeMap();
        }

        void countFaculty() 
        {
            ifstream ifs(ece_staff_details);
            if (!ifs.is_open()) {
                cerr << "ERROR: Opening file " << ece_staff_details << endl;
                return;
            }

            string line;
            while (getline(ifs, line)) {
                no_of_faculty_ECE++;
            }

            ifs.close();
        }

        void initializeMap()
        {
            ifstream details_file(ece_staff_details);
            ofstream map_file(ece_map);

            if (!details_file.is_open() || !map_file.is_open()) {
                cerr << "ERROR: Opening file " << ece_staff_details << " or " << ece_map << endl;
                return;
            }

            string line;
            while (getline(details_file, line)) {
                map_file << line << ",0" << endl; 
            }

            details_file.close();
            map_file.close();
        }
    
};

class Department : public ETE,public ECE{
    public:

        // to calculate no of faculty from each department
        int calculate(int no_of_faculty,int total_faculty,int total_rooms)
        {
            cout<<"no_of_faculty : "<<no_of_faculty<<endl;
            cout<<"total_faculty : "<<total_faculty<<endl;
            cout<<"total_rooms : "<<total_rooms<<endl;

                int dept_faculty_cnt = round(floor(no_of_faculty*total_rooms)/total_faculty);
                cout<<"faculty_cnt : "<<dept_faculty_cnt<<endl;
                return dept_faculty_cnt;
        }

         void allotment(int req_faculty_cnt,string mapfile,string Dept,string examDate)
        {
            ifstream infile(mapfile);
            if (!infile.is_open()) {
                cerr << "Error opening file for reading." << endl;
                return;
            }

            // Read data from file into a vector of pairs
            vector<pair<string, int>> data;
            string line;
            while (getline(infile, line)) {
                stringstream ss(line);
                string name, id;
                int value;
                getline(ss, name, ',');
                getline(ss, id, ',');
                ss >> value;
                data.push_back(make_pair(name + "," + id, value));
            }
            infile.close();

            // Sort the vector based on the count (integer value)
            sort(data.begin(), data.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second < b.second;
            });

            // Allot faculty members and update the allotted count
            int cnt=0;
            ofstream allot("Alloted_Staff.csv", ios::app);
            if(!allot.is_open())
            {
                cerr<<"ERROR: opending ALloted_staff for appending"<<endl;
                return;
            }
            for (auto& entry : data) {
                if(cnt==req_faculty_cnt) break;
                // Allot faculty member here, for example:
                cout << "Faculty " << entry.first << " allotted." << endl;
                allot<<examDate<<","<<entry.first<<","<<Dept<<endl;
                entry.second++; // Increment the allotted count
                cnt++;
            }
            allot.close();

            // Write the updated data back to the file
            ofstream outfile(mapfile);
            if (!outfile.is_open()) {
                cerr << "Error opening file for writing." << endl;
                return;
            }

            for (const auto& entry : data) {
                outfile << entry.first << "," << entry.second << endl;
            }
            outfile.close();

            cout << "Allotment done and updated in Alloted_Staff.csv successfully." << endl;

            
        }

};

void display(string d)
{
    string staff_fileName=d+"_Staff"+".csv";
    string filename = staff_fileName; // File name
    ifstream infile(filename); // Open file for reading

    if (!infile.is_open()) { // Check if file opening failed
        cerr << "Error opening file: " << filename << endl;
        return ;
    }

    string line;
    cout << "\n\n\t\t\t\t\t Staff details:" << endl;
    cout << "\n\t\t\t\t\t---------------------------------------------------------" << endl;
    while (getline(infile, line)) { // Read each line from the file
        cout<<"\n\n\t\t\t\t\t ";
        cout << line << endl; // Print the line to the console
    }
    cout << "\n\t\t\t\t\t---------------------------------------------------------" << endl;
    infile.close(); // Close the file
}

int register_staff(string d)
{
    string staff_fileName;
    staff_fileName=d+"_Staff";
    string name;
    string id; //short form of faculty name
        
        cout << "\n\n\t\t\t\t\t Enter the faculty name : ";
        // getline(cin,name);
        cin>>name;
        cout << "\n\n\t\t\t\t\t Enter the short form of faculty name : ";
        cin>>id;

        //to write data to respective dept staff details
        //ofstream– This class represents an output stream. It’s used for creating files and writing information to files.
        ofstream staff_file(staff_fileName+".csv" , ios :: app); 
        
        if(staff_file.is_open())
        {
            staff_file<<name<<","<<id<<endl;
            staff_file.close();
            cout<<"Data added Successfully...."<<"\n";
        }
        else{
            cerr<<"Error opening file for Writing"<<endl;
            return 1;
        }
        return 0;
}



void delete_staff(string d)
{
    string staff_fileName;
    staff_fileName=d+"_Staff"+".csv";
    string name;
    cout << "\n\n\t\t\t\t\t Enter the faculty name to remove their data : ";
    // getline(cin,name);
    cin>>name;

    //reading data
    //ifstream– This class represents an input stream. It’s used for reading information from data files.
    ifstream staff_file(staff_fileName , ios::in);

    if(staff_file.is_open())
    {
        vector<string> lines;
        string line;
        while (getline(staff_file, line))
        {
            vector<string> tokens = split(line,','); //split line by comma
            //lines will store all the faculty data except the one to be deleted
            if(tokens.size()>=2 && tokens[0] != name)
            {
                lines.push_back(line);
            }
        }
        staff_file.close();

        //writing back to the file the updated data to the file

        ofstream staff_file(staff_fileName);
        if(staff_file.is_open())
        {
            for(const string &line : lines)
            {
                staff_file<<line<<endl; //inserting in the file line by line
            }
            staff_file.close();
            cout<<"Entry for  "<<name<<" has been removed successfully."<<endl;
        }
        else{
            cerr<<"Error opening file for writing."<<endl;
        }
    }
    
    //if  file is not opened
    else{

        cerr<<"Error opening file for reading..."<<endl;
    }
}




void staff_allotment()
{
    
            system("cls"); //for clearing screen
            cout<<"\n\t\t\t------------------------------------------------------------------------------------";
            cout<<"\n\t\t\t||                       SIDDAGANGA INSTITUTE OF TECHNOLOGY                       ||";
            cout<<"\n\t\t\t------------------------------------------------------------------------------------";
            cout<<"\n\t\t\t||                 ELECTRONICS AND TELECOMMUNICATION ENGINEERING                  ||";
            cout<<"\n\t\t\t------------------------------------------------------------------------------------";
            cout<<"\n\t\t\t||                       STAFF INVILIGATION ALLOTMENT SYSTEM                      ||";
            cout<<"\n\t\t\t------------------------------------------------------------------------------------\n";
    
    ETE ete;
    ECE ece;

    Department dept;
    
    //store the number of days exam will be conducted
    int no_of_days;
    
    //store the number of rooms required for each day of exam
    int no_of_rooms;

    cout<<"\n\n\t\t\t\t\t Enter the number of days exam to be conducted : "<<endl;
    cin>>no_of_days;

    string exam_dates[no_of_days];

    cout<<"\n\n\t\t\t\t\t Enter the dates of the examination : "<<endl;
    for(int i=0;i<no_of_days;i++)
    {
        cout<<"\n\n\t\t\t\t\t  Date "<<i+1<<": ";
        cin>>exam_dates[i];
    }

    //total number of faculties in both the dept
    int total_faculty= ete.no_of_faculty_ETE + ece.no_of_faculty_ECE;

    cout<<"\n\n\t\t\t\t\t total_faculty : "<<total_faculty<<endl;

    //need to apply loop for total no of days/
    for(int i=0;i<no_of_days;i++)
    {
        cout<<"\n\n\t\t\t\t\t Enter the number of rooms required on "<<exam_dates[i]<<" : ";
        cin>>no_of_rooms;

        //-------------------------------------Calculating Requried count of facutly from each Dept process----------------------------------------------------

        //storing required ete faculty cnt
        cout<<"\n\n\t\t\t\t\t ETE count : "<<dept.calculate(ete.no_of_faculty_ETE,total_faculty,no_of_rooms)<<endl;
        int ETE_count= dept.calculate(ete.no_of_faculty_ETE,total_faculty,no_of_rooms);
        
        //storing required ece faculty cnt
        cout<<"\n\n\t\t\t\t\t ECE count : "<<dept.calculate(ece.no_of_faculty_ECE,total_faculty,no_of_rooms)<<endl;
        int ECE_count=dept.calculate(ece.no_of_faculty_ECE,total_faculty,no_of_rooms);

        int total = ETE_count+ECE_count;
        
        if(total > no_of_rooms)
        {
            ETE_count--;
        }


          cout<<"\n\n\t\t\t\t\t Req faculty from Ete : "<<ETE_count<<endl;
          cout<<"\n\n\t\t\t\t\t Req faculty from Ece : "<<ECE_count<<endl;


          //-------------------------------------Allotment process----------------------------------------------------
           //alloting ete faculty members
           dept.allotment(ETE_count,"ETE_Staff.csv","ETE",exam_dates[i]);

            //alloting ete faculty members
           dept.allotment(ECE_count,"ECE_Staff.csv","ECE",exam_dates[i]);


    }

    //5cout<<ete.no_of_faculty_ETE<<endl;

}


void mainpage()
{
    int choice;
    while (true) {
        //system("cls");
        cout << "\n\t\t\t------------------------------------------------------------------------------------";
        cout << "\n\t\t\t||                       SIDDAGANGA INSTITUTE OF TECHNOLOGY                       ||";
        cout << "\n\t\t\t------------------------------------------------------------------------------------";
        cout << "\n\t\t\t||                 ELECTRONICS AND TELECOMMUNICATION ENGINEERING                  ||";
        cout << "\n\t\t\t------------------------------------------------------------------------------------";
        cout << "\n\t\t\t||                      STAFF INVILIGATION ALLOTMENT SYSTEM                       ||";
        cout << "\n\t\t\t------------------------------------------------------------------------------------";
        cout << "\n\n\t\t\t\t\t 1. Register New Staff Details";
        cout << "\n\n\t\t\t\t\t 2. Delete the particular Staff Details";
        cout << "\n\n\t\t\t\t\t 3. Display staff details";
        cout << "\n\n\t\t\t\t\t 4. Allotment staff";
        cout << "\n\n\t\t\t\t\t 5. Exit";
        cout << "\n\t\t\t\t\t..................................";
        cout << "\n\t\t\t\t\t>> Choose Options:[1/2/3/4/5] <<";
        cout << "\n\t\t\t\t\t..................................\n";
        cout << "\n\n\t\t\t\t\t Enter Your Choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            {
            string faculty_dept;
            cout<<"\n\t\t\t\t\t Enter the deparatment of the facutly [ETE/ECE/EEE]: ";
            cin>>faculty_dept;
            register_staff(faculty_dept);   // registing staff
            }
            break;
        case 2:
            {
            string faculty_dept;
            cout<<"\n\t\t\t\t\t Enter the deparatment of the facutly [ETE/ECE/EEE]: ";
            cin>>faculty_dept;
            delete_staff(faculty_dept);   // deleting staff
            }
            break;
        case 3:
            {
                string faculty_dept;
                cout<<"\n\t\t\t\t\t Enter the deparatment of the facutly [ETE/ECE/EEE]: ";
                cin>>faculty_dept;
                display(faculty_dept);   // staff allotment
            }
            break;
        case 4:
            {
                // string faculty_dept;
                // cout<<"\n\t\t\t\t\t Enter the deparatment of the facutly [ETE/ECE/EEE]: ";
                // cin>>faculty_dept;
                staff_allotment();   // staff allotment
                display("Alloted");
            }
            break;
        case 5:
            system("cls"); //for clearing screen
            cout<<"\n\t\t\t------------------------------------------------------------------------------------";
            cout<<"\n\t\t\t||                       SIDDAGANGA INSTITUTE OF TECHNOLOGY                       ||";
            cout<<"\n\t\t\t------------------------------------------------------------------------------------";
            cout<<"\n\t\t\t||                 ELECTRONICS AND TELECOMMUNICATION ENGINEERING                  ||";
            cout<<"\n\t\t\t------------------------------------------------------------------------------------";
            cout<<"\n\t\t\t||                       STAFF INVILIGATION ALLOTMENT SYSTEM                      ||";
            cout<<"\n\t\t\t------------------------------------------------------------------------------------\n";
            cout<<"\n\t\t\t\t\t\t 1. B VAISHALI CHOUDHARY : 1SI21ET007"<<endl;
            cout<<"\t\t\t\t\t\t 2. MANISHA S CHOUDHARY : 1SI21ET026"<<endl;
            cout<<"\t\t\t\t\t\t 3. P S PRARTHANA  : 1SI21ET032"<<endl;
            cout<<"\t\t\t\t\t\t 4. RUCHITHA REDDY :  1SI21ET041"<<endl;
            cout<<"\n\t\t\t------------------------------------------------------------------------------------";
            cout<<"\n\n\t\t\t\t\t\t THANK - YOU \n\n"<<endl;
            sleep(5);
            exit(0);
            break;
        default:
            cout << "\n\n\t\t\t Invalid Choice.. Please Try Again..\n";
            break;
        }
    }
}

int main()
{
    
    mainpage();
    return 0;
}