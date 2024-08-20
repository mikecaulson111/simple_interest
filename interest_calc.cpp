#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;



int main(int argc, char* argv[]) {
    // cout << argc << argv[1] << endl;
    string temp = "";
    double loan_amt = 0;
    double interest_rate = 0.0;
    double month_payments = 0;
    double loan_hold = 0.0;
    bool print_years = false;
    bool daily_interest = false;
    cout << "Please enter the current loan amount (can be integer or double):" << endl;
    getline(cin, temp, '\n');

    loan_amt = stod(temp);
    
    cout << "Please enter the interest rate (as a decimal i.e. 8.49):" << endl;
    getline(cin, temp, '\n');
    interest_rate = stod(temp);

    cout << "Please enter the amount you pay every month (can be integer or decimal):" << endl;
    getline(cin, temp, '\n');
    month_payments = stod(temp);

    cout << "$" << std::fixed << std::setprecision(2) << loan_amt << " at " << interest_rate << "% paying $" << month_payments << endl;
    loan_hold = loan_amt;

    if ((loan_amt - month_payments) * ((interest_rate / 100.0) / 12) >= month_payments ) {
        cout << "*** PAYING THAT AMOUNT PER MONTH YOU WILL NEVER PAY OFF YOUR LOAN ***" << endl;
        return 0;
    }

    if (argc > 1) {
        if (0 == strcmp(argv[1], "-y")) {
            print_years = true;
        } else if (0 == strcmp(argv[1], "-d")) {
            daily_interest = true;
        }
    }

    double total_interest = 0;
    int months = 1;
    double year_tot_paid = 0;
    double year_tot_interest = 0;
    while (loan_amt > 0) {
        double temp = loan_amt - month_payments;
        double t2 = temp * ((interest_rate / 100.0) / 12);
        total_interest += t2;
        loan_amt = temp + t2;
        if (loan_amt < 0) {
            loan_amt = 0;
        }
        if (t2 < 0) {
            t2 = 0;
        }

        if (!print_years) {
            cout << "Month " << months << " Balance: $" << loan_amt << " Interest acrued: $" << t2 << endl;
        } else {
            if (months % 12 == 0) {
                cout << "Year " << months / 12 << " Balance: $" << loan_amt << " Interest acrued throught the year: $" << year_tot_interest << " Total paid off throught the year: $" << year_tot_paid << endl;
                year_tot_paid = 0;
                year_tot_interest = 0;
            } else if (print_years && !daily_interest) {
                year_tot_paid += month_payments;
                year_tot_interest += t2;
            }
        }
        months += 1;
    }
    cout << "Loan paid off in " << months - 1 << " months with total interest paid $" << total_interest << " on the initial $" << loan_hold << " loan" << endl;
    
    return 0;
}
