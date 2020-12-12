#pragma once

class Process{

public:

	enum Status{
		ACTIVE,
		DONE,
		READY,
		INACTIVE
	};
	
private:
	
	int id;
	int need_time;
	int appearance_time;
	int system_time;
	int run_time;
	int rr_time;
	double penalty_ratio;
	
	Status status;
	
	static int generate_id() { static int i = 0; return i++; }
	
public:
	
	Process(int need_time, Status status_in, int appearance_time)
	: need_time(need_time), status(status_in), appearance_time(appearance_time),
	id(generate_id()), system_time(0), run_time(0), penalty_ratio(0), rr_time(0) {}
		
	
	int get_id() const { return this->id; }
	int get_need_time() const { return this->need_time; }
	int get_appearance_time() const { return this->appearance_time; }
	int get_system_time() const { return this->system_time; }
	int get_run_time() const { return this->run_time; }
	int get_rr_time() const { return this->rr_time; }
	double get_penalty_ratio() { return this->penalty_ratio; }
	Status get_status() const { return this->status; }	

	void set_status(Status status) { this->status = status; }
	void set_system_time(int time) { this->system_time = time; }
	void set_rr_time(int time) { this->rr_time = time; }


	void update(int count_quanta) 
	{
		if (count_quanta >= this->appearance_time && this->status == INACTIVE)
			this->status = READY;

		if (this->status == READY || this->status == ACTIVE)
			this->system_time++;

		if (this->status == ACTIVE)
			this->run_time++;
		
		if (this->status == ACTIVE)
			this->rr_time++;
			
		if(this->status == READY)
			this->penalty_ratio = double(this->system_time + this->need_time) / this->need_time;
	}
	
	friend std::ostream& operator<<(std::ostream& os, Status status)
	{
		switch (status)
		{
		case Process::ACTIVE:
			os << "ACT";
			break;
		case Process::READY:
			os << "READY";
			break;
		case Process::DONE:
			os << "DONE";
			break;
		case Process::INACTIVE:
			os << "INACT";
			break;
		}
		return os;
	}	
};
