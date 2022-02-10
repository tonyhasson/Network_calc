#include <iostream>
#include <string>
#include <map>
using namespace std;
#pragma warning(disable:4996)

////////////////////////////helper functions




// Map for converting hexadecimal
// values to decimal
map<char, int> hex_value_of_dec(void)
{
	// Map the values to decimal values
	map<char, int> m{ { '0', 0 }, { '1', 1 },
					  { '2', 2 }, { '3', 3 },
					  { '4', 4 }, { '5', 5 },
					  { '6', 6 }, { '7', 7 },
					  { '8', 8 }, { '9', 9 },
					  { 'A', 10 }, { 'B', 11 },
					  { 'C', 12 }, { 'D', 13 },
					  { 'E', 14 }, { 'F', 15 } };

	return m;
}

// Map for converting decimal values
// to hexadecimal
map<int, char> dec_value_of_hex(void)
{
	// Map the values to the
	// hexadecimal values
	map<int, char> m{ { 0, '0' }, { 1, '1' },
					  { 2, '2' }, { 3, '3' },
					  { 4, '4' }, { 5, '5' },
					  { 6, '6' }, { 7, '7' },
					  { 8, '8' }, { 9, '9' },
					  { 10, 'A' }, { 11, 'B' },
					  { 12, 'C' }, { 13, 'D' },
					  { 14, 'E' }, { 15, 'F' } };

	return m;
}

// Function to add the two hexadecimal numbers
string Add_Hex(string a, string b)
{
	map<char, int> m = hex_value_of_dec();
	map<int, char> k = dec_value_of_hex();

	// Check if length of string first is
	// greater than or equal to string second
	if (a.length() < b.length())
		swap(a, b);

	// Store length of both strings
	int l1 = a.length(), l2 = b.length();

	string ans = "";

	// Initialize carry as zero
	int carry = 0, i, j;

	// Traverse till second string
	// get traversal completely
	for (i = l1 - 1, j = l2 - 1;
		j >= 0; i--, j--) {

		// Decimal value of element at a[i]
		// Decimal value of element at b[i]
		int sum = m[a[i]] + m[b[j]] + carry;

		// Hexadecimal value of sum%16
		// to get addition bit
		int addition_bit = k[sum % 16];

		// Add addition_bit to answer
		ans.push_back(addition_bit);

		// Update carry
		carry = sum / 16;
	}

	// Traverse remaining element
	// of string a
	while (i >= 0) {

		// Decimal value of element
		// at a[i]
		int sum = m[a[i]] + carry;

		// Hexadecimal value of sum%16
		// to get addition bit
		int addition_bit = k[sum % 16];

		// Add addition_bit to answer
		ans.push_back(addition_bit);

		// Update carry
		carry = sum / 16;
		i--;
	}

	// Check if still carry remains
	if (carry) {
		ans.push_back(k[carry]);
	}

	// Reverse the final string
	// for desired output
	reverse(ans.begin(), ans.end());

	// Return the answer
	return ans;
}





//turn decimal number to binary
string decToBinary(int n)
{
	// array to store binary number
	int binaryNum[32];
	string result="";
	// counter for binary array
	int i = 0;
	while (n > 0) {

		// storing remainder in binary array
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}

	// printing binary array in reverse order
	for (int j = i - 1; j >= 0; j--)
	{
		
		result.append(to_string(binaryNum[j]));
	}
	
	return result;
}


////////////////////////////////Subnet calc:


//get subnet number
int extract_subnet_num(string str)
{
	int i = 0,num=0;
	while(str[i++]!='/');
	while (i < str.length())
	{
		num *= 10;
		num += str[i++] - '0';
	}
	return num;
}

//turn string into binary string
string str_bin(string str)
{
	if (str == "0.0.0.0/0")
	{
		return str;
	}
	long num = 0;
	
	string new_chosen;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '/')
		{
			break;
		}
		if (str[i] != '.')
		{
			num *= 10;
			num += str[i] - '0';
		}
		else
		{
			
			string num_str = decToBinary(num);
			for (int j = 0; j < 8 - num_str.length(); j++)
			{
				new_chosen.append("0");
			}
			new_chosen.append(num_str);
			new_chosen.append(".");
			num = 0;
		}
	}
	
	string num_str = decToBinary(num);
	for (int j = 0; j < 8 - num_str.length(); j++)
	{
		new_chosen.append("0");
	}
	new_chosen.append(num_str);

	return new_chosen;
}

//send strings to str_bin
void change_to_bin(string* chosen, string** arr, int size)
{
	
	*chosen = str_bin(*chosen);

	for (int i = 0; i < size; i++)
	{
		(*arr)[i] = str_bin((*arr)[i]);
	}
}

//get . out of strings
string clean_string(string clean_me)
{
	string clean = clean_me;
	clean.erase(remove(clean.begin(), clean.end(), '.'), clean.end());
	return clean;
}

//add to binary string together
string add_bin(string str1, string str2)
{
	
	string result = "";
	int temp = 0;
	int size_a = str1.size() - 1;
	int size_b = str2.size() - 1;
	while (size_a >= 0 || size_b >= 0 || temp == 1) {
		temp += ((size_a >= 0) ? str1[size_a] - '0' : 0);
		temp += ((size_b >= 0) ? str2[size_b] - '0' : 0);
		result = char(temp % 2 + '0') + result;
		temp /= 2;
		size_a--; size_b--;
	}
	return result;
	
}

//check if chosen ip is in subnet
bool check_exist(string chosen,string compare,int subnet_num)
{
	
	//find if chosen is between compare and compare+(2^(32-subnet_num))-1     (all in binary!)
	string subnet_add = decToBinary(int(pow(2, 32-subnet_num) - 1));
	string new_comp = clean_string(compare);
	string new_chosen = clean_string(chosen);
	string top_compare = add_bin(new_comp, subnet_add);
	if (new_chosen >= new_comp && new_chosen <= top_compare)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


//get max amount of compatible numbers
int get_max(string chosen,string compare,int subnet_num)
{
	if (compare == "0.0.0.0/0")
	{
		return -1;
	}
	if (check_exist(chosen, compare, subnet_num) == false)
	{
		return 0;
	}
	int count = 0;

	for (int i = 0; i < subnet_num; i++)
	{
		if (chosen[i] != compare[i])
		{
			break;
		}
		if (chosen[i] != '.')
		{
			count++;
		}
	}
	return count;
	
	
}


//find the best subnet between the options entered
void find_best_subnet(string chosen,string* arr, int size)
{	
	string* arr_tmp=new string[size];
	for (int i = 0; i < size; i++)
	{
		arr_tmp[i] = arr[i];
	}
	change_to_bin(&chosen,&arr_tmp, size);
	int max_count = 0,tmp_count,best_index,subnet_zero_index;
	bool find_zero_subnet = false;
	for (int i = 0; i < size; i++)
	{
		tmp_count = get_max(chosen, arr_tmp[i],extract_subnet_num(arr[i]));//if 0.0.0.0/0 return -1
		if (tmp_count == -1)
		{
			find_zero_subnet = true;
			subnet_zero_index = i;
		}
		else if (tmp_count > max_count)
		{
			max_count = tmp_count;
			best_index = i;
			
		}
	}
	
	if (max_count == 0 && find_zero_subnet == false)
	{
		cout << "error!" << endl;
	}
	else if (max_count == 0 && find_zero_subnet == true)
	{
		cout << "best subnet is number: " << subnet_zero_index + 1 << "\nthe subnet is :" << arr[subnet_zero_index] << endl;
	}
	else if (max_count > 0)
	{
		cout << "best subnet is number: " << best_index + 1 << "\nthe subnet is :" << arr[best_index] << endl;
	}

	delete[] arr_tmp;
	
}

////////////////udp header


//turn long into hexa string
string get_hexa(long port)
{
	
	char l_pCharRes[100]="";
	sprintf(l_pCharRes, "%X", port);
	string str = l_pCharRes;
	if (str.length() < 4)
	{
		str.insert(0, 4 - str.length(), '0');
	}
	
	
	
	return str;
	
}

//subtract FFFF-sum (used from checksum)
string sub_FFFF(string sum)
{
	long FFFF = 65535;
	long num = std::stoi(sum, 0, 16);
	return get_hexa(FFFF - num);

}


//create the check sum out of the 2 ports + buffer
string create_check_sum(string src, string dest, string buff)
{
	//sum between src and dest
	string sum=Add_Hex(src,dest);
	
	while (sum.length() > 4)
	{
		string c = to_string(sum[0]- '0');
		sum.erase(0, 1);
		
		//convert to hexa
		sum = Add_Hex(sum, c);
		
		//add c into hexa
		//if sum is still >4 do it again

	}
	
	sum = Add_Hex(sum, buff);
	while (sum.length() > 4)
	{
		string c = to_string(sum[0] - '0');
		sum.erase(0, 1);
		//convert to hexa
		sum = Add_Hex(sum, c);
		//add c into hexa
		//if sum is still >4 do it again

	}
	
	

	return sub_FFFF(sum);

}


//creates udp header
void create_udp_header(long src, long dest,long buff)
{
	string result,src_str= get_hexa(src),dest_str= get_hexa(dest),src_buff= get_hexa(buff + 8);
	result.append(src_str);
	result.append(dest_str);
	result.append(src_buff);
	string check_sum = create_check_sum(src_str, dest_str, src_buff);
	result.append(check_sum);
	cout << "The UDP header is :" << result << endl;
}



int main()
{
	

	//working example:

	//subnet masking

	/*string chosen_str = "212.190.47.150", arr_options[4] = { "212.0.0.0/9","208.0.0.0/4","212.160.0.0/11","0.0.0.0/0" };
	find_best_subnet(chosen_str, arr_options, 4);*/

	
	/*string chosen_str = "132.13.175.90", arr_options[5] = { "132.13.168.0/21","132.13.160.0/21","132.13.168.0/22","132.13.175.0/26","0.0.0.0/0" };
	find_best_subnet(chosen_str, arr_options, 5);*/


	//udp header
	//create_udp_header(43455, 50069, 992);
	


	


	bool choice = false;
	int choose;
	char c;
	cout << "Welcome to Tony's networking calculator!" << endl;
	do
	{
	cout << "Please choose from the a number from the options below:" << endl;
	cout << "Subnet masking finder: 1" << endl;
	cout << "UDP header calculator: 2" << endl;
	cin >> choose;
	switch (choose)
	{
		case 1:
		{
			string chosen_str, * arr_options;
			cout << "Enter like this: chosen_str = 212.190.47.150 \n option_example: 212.0.0.0/9\n" << endl;
			cout << "Enter IP address you want to check: " << endl;
			cin >> chosen_str;
			int size;
			cout << "Enter amount of IP subnet options: " << endl;
			cin >> size;
			arr_options = new string[size];
			for (int i = 0; i < size; i++)
			{
				cout << "Enter subnet number: " << i + 1 << endl;
				cin >> arr_options[i];
			}
			find_best_subnet(chosen_str, arr_options, size);
			cout << "\n" << endl;
			delete[] arr_options;
			break;
		}

		case 2:
		{
			long src, dest, buff;
			cout << "Enter only numbers!!! buffer is in Bytes\n" << endl;
			cout << "Enter source port:" << endl;
			cin >> src;
			cout << "Enter destination port:" << endl;
			cin >> dest;
			cout << "Enter buffer:" << endl;
			cin >> buff;

			create_udp_header(src, dest, buff);

			
			break;
		}

		default:
		{
			cout << "chosen wrong number,please choose again!" << endl;
			choice = true;
			break;
		}
	}
	cout << "\nDo you want to use the calculator again? Y / N " << endl;
	cin >> c;
	if (c == 'Y' || c == 'y')
	{
		choice = true;
	}
	else
	{
		choice = false;
	}
	
	} while (choice);

	cout << "Good Bye!" << endl;
	
	
}


