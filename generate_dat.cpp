#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <class T1, class T2, class Pred = std::greater<T2> >
struct sort_pair_second {
	    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
			Pred p;
			return p(left.second, right.second);
		}
};

int main(){
	unordered_map<string, int> vocab;
	string str; string sstr;
	string cnt;
	string address = "/home/steve/Bayes_Proj/extracted1/";
	string filename;
	string vocab_list = "/home/steve/Bayes_Proj/corpus1.whole_dict-0.csv"; // the source of vocab_picked

	int document_size = 2000;
	int count = 0; // default value is the index of the first word

	ofstream fout;
	fout.open("/home/steve/Bayes_Proj/PMC1_t.dat",ios::app);

	ofstream fout_vb;
	fout_vb.open("/home/steve/Bayes_Proj/vocab1.txt",ios::app);

	/*Define Vocabulary of the Corpus*/
	//read from all csv files
	/*ifstream list("/home/steve/Bayes_Proj/fn.txt");
	while(list >> filename){
		string fn = address+filename;
		//cout << fn << endl;
		ifstream fin(fn);
		if (!fin.is_open()) cout << "CANT OPEN: "<< fn << endl;
		fin >> str;//flush out first line
		while (fin>>str){
			stringstream ss(str);
			//cout << str << endl;
			getline(ss, sstr, ',');
			//cout << sstr << endl;
			auto search = vocab.find(sstr);
			if (search == vocab.end()){
				vocab.insert({sstr, count});	
				count ++;
				fout_vb << sstr << endl;
			}
		}	
		fin.close();
	}
	list.close();*/

	ifstream fin_vb;
	fin_vb.open(vocab_list);

	string word;
	int index = 1;//starting INDEX
	fin_vb >> word; //flush out first line
	while(fin_vb >> word && index < document_size){
		stringstream ss(word);
		//cout << str << endl;
		getline(ss, sstr, ',');
		vocab.insert({sstr, index});	
		fout_vb << sstr << endl;
		index ++;
	}
	fout_vb.close();	
	fin_vb.close();

	ifstream list1("/home/steve/Bayes_Proj/fn1_t.txt");
	//Generate each line according to a csv file
	while (list1>>filename)
	{

		/*int num_l = 0;
		ifstream fin2(address+filename);
		fin2 >> str;
		while (getline(fin2,str)){
				num_l ++;
		}
		fout << num_l <<" ";
		fin2.close();*/

		vector<std::pair<int,int> > doc_container;
		doc_container.clear();

		//cout << num_l << endl;
		ifstream fin1(address+filename);
		fin1 >> str;
		while (fin1>>str){
			//cout << str << endl;
			istringstream ss(str);
			getline(ss, sstr, ',');
			getline(ss, cnt, ',');	
			//cout << sstr << ";;;;" << endl;
			count = std::stoi(cnt);
			//cout  << sstr << ":" << count<< endl;
			auto search = vocab.find(sstr);
			//cout << index << endl;
			if (search != vocab.end()){

				index = search->second;
				//cout << index << ":" << count << " " << endl;
				//cout << index << endl;
				doc_container.push_back({index, count});

			}
		}

		//fout << endl;
		//std::sort(doc_container.begin(), doc_container.end(), sort_pair_second<int, int>());
		fin1.close();
		
		fout << doc_container.size() << " ";
		//if (num_l > document_size){
		for (size_t i = 0; i  < doc_container.size(); i++){
			fout << doc_container[i].first << ":" << doc_container[i].second <<" ";
		}
		/*}
		else {
			for (int i = 0; i  < num_l; i++){
				fout << doc_container[i].first << ":" << doc_container[i].second <<" ";
			}
		}	*/
		fout << endl;
	}
	
	fout.close();
	return 0;
}
