//Franciscon Rocha
//Iker Guerrero
//Juan Carlos Llanos
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct {             // Structure declaration
  int position;        
  string presence;  
} kmpResult;       // Structure variable

 struct {
    int initialPosition;
    int finalPosition;
    int palindromeMaxLenght;
} largestPalindrome;

//Function to print vectors
void printCharVectors(vector<char> v){
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
    
}

//Function to convert file to string
string fileToString(string fileName){
    string line;
    string text; //Here is saved the string.txt text
    ifstream document(fileName);
    while (getline(document,line))
    {
        text = text + line;
    }
    document.close();
    return text;
}

//Function to convert string to vector
vector<char> strToVector(string s){
    vector<char> transmissionX;
    for (int i = 0; i < s.length(); i++)
    {
        transmissionX.push_back(s[i]);
    }
    return transmissionX;
}

 
/*Function to implement the KMP algorithm.
As parameter receives the two files and a bool that indicates the palindrome(ONLY) mode activated.
NOTE: I CONFUSED AND I THOUGHT PALINDROME WAS THE PATTERN IN REVERSE, IF YOU ACTIVATE THE PALINDROME OPTION
IT WILL NOT SEARCH REALLY A PALINDROME THATS WHY I CREATED ANOTHER FUNCTION THAT REALLY FINDS PALINDROMES (longestPalindrome)
*/ 
void KMP(string transmissionX, string mCodeX, bool palindrome = false) 
{
    //We initialize all variables in 0
    kmpResult.position = 0;
    kmpResult.presence = "false";
    largestPalindrome.finalPosition = 0;
    largestPalindrome.initialPosition = 0;
    largestPalindrome.palindromeMaxLenght = 0;

    string stringMCode = fileToString(mCodeX);

    //We convert fileName to string and then to a vector of chars
        vector<char> transmissionChars = strToVector(fileToString(transmissionX));
        vector<char> codeChars = strToVector(stringMCode);

    //Conditional that reverses the pattern in case palindrome mode is activated
    if (palindrome == true)
    {
        reverse(codeChars.begin(), codeChars.end());
    }

    //We calculate how many chars the texts have
	int m = transmissionChars.size();
	int n = codeChars.size();

	// if codeChars is an empty vector
	if (n == 0)
	{
        //The codeChars occurs with shift 0
        kmpResult.position = 0;
        kmpResult.presence = "true";
        if (palindrome == false)
        {
            cout << kmpResult.presence << " " << kmpResult.position << " " << transmissionX << " contiene el código: " << stringMCode << " de: " << mCodeX << endl;
        } else{
            //If is an empty vector, then the result must be 0 0
            cout << kmpResult.position << " " << kmpResult.position << endl;
        }
        
		return;
	}

	// if transmissionChars' length is less than that of codeChars's
	if (m < n)
	{
        kmpResult.position = -1;
        kmpResult.presence = "false";
		cout << kmpResult.presence << " " << transmissionX << " contiene el código: " << stringMCode << " de: " << mCodeX << endl;
		return;
	}

	// next[i] stores the index of the next best partial match
	int next[n + 1];

	for (int i = 0; i < n + 1; i++) {
		next[i] = 0;
	}

	for (int i = 1; i < n; i++)
	{
		int j = next[i + 1];

		while (j > 0 && codeChars[j] != codeChars[i]) {
			j = next[j];
		}

		if (j > 0 || codeChars[j] == codeChars[i]) {
			next[i + 1] = j + 1;
		}
	}

	for (int i = 0, j = 0; i < m; i++)
	{
		if (transmissionChars[i] == codeChars[j])
		{
			if (++j == n) {
                kmpResult.position = i-j+1;
                kmpResult.presence = "true";
                if (palindrome == false){
                    //cout << kmpResult.presence << " " << kmpResult.position << " " << transmissionX << " contiene el código: " << stringMCode << " de: " << mCodeX << endl;
                    } else{
                    //largestPalindrome.initialPosition = kmpResult.position + n;
                    //largestPalindrome.finalPosition = kmpResult.position + 1;
                    int auxMaxInitialPosition = kmpResult.position + n;
                    int auxMaxFinalPosition = kmpResult.position + 1;
                    int auxMaxLength = (kmpResult.position + n) - (kmpResult.position);//length of the actual found palindrome
                    if (auxMaxLength > largestPalindrome.palindromeMaxLenght)
                    {
                        largestPalindrome.palindromeMaxLenght = auxMaxLength;
                        //Save initial and final positions
                        largestPalindrome.finalPosition = auxMaxFinalPosition;
                        largestPalindrome.initialPosition = auxMaxInitialPosition ;

                    }
                    
                    }
			}
		}
		else if (j > 0)
		{
			j = next[j];
			i--;	// since `i` will be incremented in the next iteration
		}
        
        if (i == m-1 && transmissionChars[i] != codeChars[j]){
            cout << kmpResult.presence << " " << kmpResult.position << " " << transmissionX << " contiene el código: " << stringMCode << " de: " << mCodeX << endl;
        }
	}

    if (palindrome == true)
    {
        cout << largestPalindrome.initialPosition << " " << largestPalindrome.finalPosition << " para archivo: " << transmissionX << endl;
    }
    
}

//Function to find the largest palindrome
	string longestPalindrome(string s) { //We receive the string as parameter
		int n=s.length(),mx=0;
		string start="",end="";
		string resStart="",resEnd="";
		for(int i=0;i<n;i++) {
			int l=i-1;
			int r=i+1;
			end=s[i];
			start="";
			while(l>=0&&r<n&&s[l]==s[r]) {
				start+=s[l--];
				end+=s[r++];
			}
			if(start.length()+end.length()>mx) {
				mx=start.length()+end.length();
				resStart=start;
				resEnd=end;
			}

			l=i;
			r=i+1;
			end="";
			start="";
			while(l>=0&&r<n&&s[l]==s[r]) {
				start+=s[l--];
				end+=s[r++];
			}
			if(start.length()+end.length()>mx) {
				mx=start.length()+end.length();
				resStart=start;
				resEnd=end;
			}
		}
		reverse(resStart.begin(),resStart.end());
		return resStart+resEnd;
	}

//Function to find the Common Largest Substring
string LCSubStr(string X, string Y)
{
    // Find length of both the strings.
    int m = X.length();
    int n = Y.length();
 
    // Variable to store length of longest
    // common substring.
    int result = 0;
 
    // Variable to store ending point of
    // longest common substring in X.
    int end;
 
    // Matrix to store result of two
    // consecutive rows at a time.
    int len[2][n + 1];
 
    // Variable to represent which row of
    // matrix is current row.
    int currRow = 0;
 
    // For a particular value of i and j,
    // len[currRow][j] stores length of longest
    // common substring in string X[0..i] and Y[0..j].
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                len[currRow][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1]) {
                len[currRow][j] = len[1 - currRow][j - 1] + 1;
                if (len[currRow][j] > result) {
                    result = len[currRow][j];
                    end = i - 1;
                }
            }
            else {
                len[currRow][j] = 0;
            }
        }
 
        // Make current row as previous row and
        // previous row as new current row.
        currRow = 1 - currRow;
    }
 
    // If there is no common substring, print -1.
    if (result == 0) {
        return "-1";
    }
 
    // Longest common substring is from index
    // end - result + 1 to index end in X.
    return X.substr(end - result + 1, result);
}

//KMP function to find positions
void KMP_positions(string text, string pattern, string archivo = "archivo")
{
    int contador = 0;
	int m = text.length();
	int n = pattern.length();

	// if pattern is an empty string
	if (n == 0)
	{
		cout << "The pattern occurs with shift 0";
		return;
	}

	// if text's length is less than that of pattern's
	if (m < n)
	{
		cout << "Pattern not found";
		return;
	}

	// next[i] stores the index of the next best partial match
	int next[n + 1];

	for (int i = 0; i < n + 1; i++) {
		next[i] = 0;
	}

	for (int i = 1; i < n; i++)
	{
		int j = next[i + 1];

		while (j > 0 && pattern[j] != pattern[i]) {
			j = next[j];
		}

		if (j > 0 || pattern[j] == pattern[i]) {
			next[i + 1] = j + 1;
		}
	}

	for (int i = 0, j = 0; i < m; i++)
	{
		if (text[i] == pattern[j])
		{
			if (++j == n) {
				cout << i - j + 2 << " " << i-j+1+n << " en archivo de transmisión: " << archivo << endl;
                contador++;
			}
		}
		else if (j > 0)
		{
			j = next[j];
			i--;	// since `i` will be incremented in the next iteration
		}
	}
}


//Function main to call all the other functions
int main()
{
    //Defition of the name of the files
    string transmission1 = "transmission1.txt";
    string transmission2 = "transmission2.txt";
    string mcode1 = "mcode1.txt";
    string mcode2 = "mcode2.txt";
    string mcode3 = "mcode3.txt";

    //String variables that contain the transmissions
    string s1 = fileToString(transmission1);
    string s2 = fileToString(transmission2);
    
	KMP(transmission1,mcode1);
    KMP(transmission1,mcode2);
    KMP(transmission1,mcode3);
    KMP(transmission2,mcode1);
    KMP(transmission2,mcode2);
    KMP(transmission2,mcode3);

    /* //This is comented because is the code that finds the malicious code in reverse
    KMP(transmission1,mcode1,true);
    KMP(transmission1,mcode2,true);
    KMP(transmission1,mcode3,true);
    KMP(transmission2,mcode1,true);
    KMP(transmission2,mcode2,true);
    KMP(transmission2,mcode3,true);
    */

    //Function that returns the longest palindrome in a String
    string sP1 = longestPalindrome(s1); // String palindrome 1
    string sP2 = longestPalindrome(s2); //String palindrome 2

    
    //Function that gives us the positions and we print them
    cout << "Palindromo más largo: ";
    KMP_positions(s1,sP1,transmission1);
    cout << "Palindromo más largo: ";
    KMP_positions(s2,sP2,transmission2);
    
    //Function that returns the longest common substring in a String
    string sCL = LCSubStr(s1,s2); //String Common Longest

    //Function that gives us the positions and we print them
    cout << "Subcadena en común más larga: ";
    KMP_positions(s1,sCL,transmission1);
    cout << "Subcadena en común más larga: ";
    KMP_positions(s2,sCL,transmission2);
    
        
	return 0;
}