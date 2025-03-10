#include "Service.h"


vector<Bill> Service::get_sorted_bills()
{
	vector<Bill> bills = this->repo.get_bills();
	sort(bills.begin(), bills.end(), [](const Bill& a, const Bill& b) 
		{
			return a.get_company() < b.get_company();
		});
	return bills;

}

double Service::calculate_total(string company)
{
	double total = 0;
	for (auto& bill : this->repo.get_bills())
	{
		if (bill.get_company() == company && !bill.get_is_paid())
			total += bill.get_sum();
	}
	return total;
}