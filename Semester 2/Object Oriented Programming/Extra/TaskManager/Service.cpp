#include "Service.h"

vector<Task> Service::get_tasks_sorted()
{
	vector<Task> tasks_sorted= this->repo.get_tasks();
	auto comparator = [](Task& a, Task& b)
		{
			if (a.get_priority() == b.get_priority())
				return a.get_duration() < b.get_duration();
			return a.get_priority() < b.get_priority();
		};
	sort(tasks_sorted.begin(), tasks_sorted.end(), comparator);
	return tasks_sorted;

}

