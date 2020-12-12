#include <iostream>
#include <vector>
#include <iomanip>
#include "process.h"

void print_proc(std::vector<Process*>& all_proc);
void print_status_proc(std::vector<Process*>& all_proc, int count_quanta);
void print_status_proc_hprn(std::vector<Process*>& all_proc, int count_quanta);

void RR(std::vector<Process*>& all_proc)
{
	int const Q = 5; //Выделяемый квант времени
	bool run_status = false;
	Process* runnable_proc = nullptr;
	for (auto& i : all_proc)
	{
		if (i->get_status() == Process::ACTIVE)
		{
			run_status = true;
			runnable_proc = i;
			break;
		}
	}

	if (run_status) /*Выполнился ли процесс?*/
	{
		if (runnable_proc->get_run_time() >= runnable_proc->get_need_time()) 
		{
			runnable_proc->set_status(Process::DONE);
			run_status = false;
		}
		
		if (runnable_proc->get_rr_time() >= Q && run_status) 
		{
			runnable_proc->set_status(Process::READY);
			runnable_proc->set_system_time(0);
			runnable_proc->set_rr_time(0);
			run_status = false;
		}
	}
	
	if (!run_status) /*выбираем процесс для исполнения*/
	{
		runnable_proc = nullptr;
		int min_need = -1;
		for (auto& i : all_proc)
		{
			if (i->get_system_time() > min_need && i->get_status() == Process::READY)
			{
				runnable_proc = i;
				min_need = i->get_system_time();
			}
		}

		if (min_need != -1)
		{
			runnable_proc->set_status(Process::ACTIVE);
		}
	}
}

int main() {
	
	system("chcp 1251>nul");
	
	std::vector<Process*> all_proc;
	

	all_proc.push_back(new Process(7, Process::READY, 0));
	all_proc.push_back(new Process(6, Process::READY, 0));
	all_proc.push_back(new Process(4, Process::INACTIVE, 6));
	all_proc.push_back(new Process(4, Process::INACTIVE, 3));
	all_proc.push_back(new Process(7, Process::INACTIVE, 6));
	all_proc.push_back(new Process(6, Process::INACTIVE, 2));
	all_proc.push_back(new Process(3, Process::INACTIVE, 9));

	print_proc(all_proc);
	std::cout << "Выполнение: " << std::endl;


	bool done = false;
	int count_quanta = 0;
	while (!done)
	{

		RR(all_proc);

		//проверка, можно ли завершать выполнение цикла
		done = true;
		for (auto& i : all_proc)
		{
			if (i->get_status() != Process::DONE)
			{
				done = false;
				break;
			}
		}

		if (!done)
		{
			for (auto& i : all_proc) /*обновление процессов*/
				i->update(count_quanta);
		}

		//вывод состояния процессов
		print_status_proc(all_proc, count_quanta);
		count_quanta++;

		system("pause>nul");
	}

	for (auto& i : all_proc)
		delete i;	
	
	return 0;
}

void print_proc(std::vector<Process*>& all_proc)
{
	std::cout << "Процессы: " << std::endl;
	std::cout << "id:\t";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << i->get_id();
	}
	std::cout << std::endl;
	std::cout << "t выполнения: ";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << i->get_need_time();
	}
	std::cout << std::endl;
	std::cout << "t появления: ";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << i->get_appearance_time();
	}
	std::cout << std::endl;
}

void print_status_proc(std::vector<Process*>& all_proc, int count_quanta)
{
	std::cout << "\t";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << i->get_status();
	}
	std::cout << "\t" << count_quanta << " - квант" << std::endl;
}

void print_status_proc_hprn(std::vector<Process*>& all_proc, int count_quanta)
{
	std::cout << std::setprecision(3);
	std::cout << "\t";
	for (auto& i : all_proc)
	{		
		if(i->get_status() == Process::READY)
			std::cout << "\t" << i->get_penalty_ratio();
		else
			std::cout << "\t" << i->get_status();
	}
	std::cout << "\t" << count_quanta << " - квант" << std::endl;
}

/*void print_stat(std::vector<Process*>& all_proc)
{
	std::cout << "t в системе:";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << i->get_system_time();
	}
	std::cout << std::endl;

	std::cout << "Потеряно t:";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << i->get_system_time() - i->get_need_time();
	}
	std::cout << std::endl;

	std::cout << std::setprecision(3);

	std::cout << "Отн. реакт.:";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << double(i->get_need_time()) / i->get_system_time();
	}
	std::cout << std::endl;

	std::cout << "Штрафное отн.:";
	for (auto& i : all_proc)
	{
		std::cout << "\t" << double(i->get_system_time()) / i->get_need_time();
	}
	std::cout << std::endl;
}*/
