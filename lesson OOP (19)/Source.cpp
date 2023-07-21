#include <iostream>
#include <vector>

#include <map>
#include <set>
#include <unordered_set> // ��������� �������� �� ������������ � ������� ���� 

#include <algorithm>

struct Record
{
	int id;
	std::string name;
	double vage;

	// ����� ������ - ��������� ������, ��� ��� ����������� ������������� ���������.
	bool operator <(const Record& obj)const
	{
		return id < obj.id;
	}
	
	bool operator==(const Record& obj)const
	{
		return id == obj.id && name == obj.name && vage == obj.vage;
	}

};

namespace std 
{
	template<>
	struct hash <Record> // ��������� ������� ���������� ������ �������.
	{
		size_t operator()(const Record& obj) const
		{
			// ����� ��� ������� �� ������� ����. 
			// �������� ��������� �� 1 ��� �����.
			// ����� ��� ������� �� ������� ����.
			// ��������� ����������� ��� ����� ����������� � ��������� ��� ��������.

			using std::size_t;
			using std::hash;
			return (hash <size_t> () (obj.id)) ^ 
				   (hash <std::string> () (obj.name) << 1) ^ 
				   (hash <double> () (obj.vage) << 1);
		}
	};
}

void fO0() {
	std::unordered_set <Record> col1;
	col1.insert(Record());
	std::map <int, Record> col2;
	Record a{ 1 , "Vova", 56034.6 };
	col2.insert(std::pair <int, Record> (a.id, a));


}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::vector <int> data;
	data.reserve(10'000); // ���������� 10000. ������ ��������, ���� ������� ��� �����.
	// data.push_back(067);

	for (size_t i = 0; i < data.capacity(); i++) // ����� ��������� ���� �������.
	{
		data.emplace_back(::rand() % 10'000); // emplace_back - ������ ����� ������ �� ������ ������� ������.
	}
	
	// ���� ������� �� �������. 0(n).
	// ���� ������ ����������. 0(n).
	// ��������� �������� ���������� �����������.
	
	std::set <int> uniq_elemets;
	
	for (size_t i = 0; i < data.size(); i++)
	{
		uniq_elemets.insert(data[i]);
	}
	
	std::cout << data.size() << " all data\n" << 
		 uniq_elemets.size() << " different data\n";

	std::vector <int> uniq_data;
	for (auto &el : data)
	{
		auto find = std::find(uniq_data.begin(), uniq_data.end(), el);
		if (find == uniq_data.end())
		{
			uniq_data.push_back(el);
		}
	}// n(n*n)
	
	std::cout << std::endl;

	std::cout << data.size() << " all data\n" <<
		uniq_data.size() << " different data\n";

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	std::cout << std::endl;

	std::vector <int> data_other;
	data_other.reserve(10'000);

	for (size_t i = 0; i < data_other.capacity(); i++) // ����� ��������� ���� �������.
	{
		data_other.emplace_back(-5000 + ::rand() % 10'000);
	}
	
	std::set <int> uniq_elemets_other;

	for (size_t i = 0; i < data_other.capacity(); i++)
	{
		uniq_elemets_other.insert(data_other[i]);
	}

	std::cout << data_other.size() << " all other data\n" <<
		uniq_elemets_other.size() << " different other data\n";


	std::vector <int> result;
	std::set_intersection(uniq_elemets.begin(), // set_intersection - ��� ��������� ��������� ������� ������������.
						  uniq_elemets.end(),
						  uniq_elemets_other.begin(), 
		                  uniq_elemets_other.end(),
						  std::back_inserter(result) // back_inserter - ������������� �� ���������� ��������� � ������� ��� ����� ����������.
		                  );
	
	std::cout << "\n";
	std::cout << result.size() << " intersect volume\n";

	return {};
}

