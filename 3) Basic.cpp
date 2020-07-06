#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;
//function declarations
void Convert(const string & Infix, string & Postfix);
bool IsOperand(char ch);
bool TakesPrecedence(char OperatorA, char OperatorB);

/*My functions I've added*/
string Change_me(string);
string Insert_comma(string);
bool Check_valid(string);
double Eval(string[]);
void Next(string);

int main()
{
   char Reply;

   do
    {
    	string Infix, Postfix; 	// local to this loop

      	cout <<"\n    Enter your expression without spaces:\n\n";
     	cin >> Infix;
      
        if(Check_valid(Infix)==true)
        {
			string temp;
	        temp = Change_me(Infix);
	
	        Convert(temp, Postfix);
	      
	        cout << "The equivalent postfix expression is:" << endl;
	        <<Insert_comma(Postfix);
	
	        string hold;
	        hold = Insert_comma(Postfix);
	         
	        cout<<"\n\nThe answer is:";
	        Next(hold);
	 
	        cout << endl << "\nDo another (y/n)? ";
	        cin >> Reply;
        }
        
        else
        {
        	cout<<"Now what did I say about using variables huh?\n";
            cout << endl << "Do another (y/n)? ";
            cin >> Reply;
        }       
          
    }	while (tolower(Reply) == 'y');

   	return 0;
}


/* Given:  ch   A character.
   Task:   To determine whether ch represents an operand (here understood
           to be a single letter or digit).
   Return: In the function name: true, if ch is an operand, false otherwise.
*/
bool IsOperand(char ch)
{
 	 if (((ch >= 'a') && (ch <= 'z')) ||      ((ch >= 'A') && (ch <= 'Z')) ||      ((ch >= '0') && (ch <= '9')))
    	return true;
    	
	else
		return false;
}

/* Given:  OperatorA    A character representing an operator or parenthesis.
           OperatorB    A character representing an operator or parenthesis.
   Task:   To determine whether OperatorA takes precedence over OperatorB.
   Return: In the function name: true, if OperatorA takes precedence over
           OperatorB.
*/

bool TakesPrecedence(char OperatorA, char OperatorB)
{
   if (OperatorA == '(')
      return false;
      
   else if (OperatorB == '(')
      return false;
      
   else if (OperatorB == ')')
      return true;
      
   else if ((OperatorA == '*') || (OperatorA == '/'))
      return true;
      
   else if ((OperatorB == '*') || (OperatorB == '/'))
      return false;
      
   else
      return true;

}

/* Given:  Infix    A string representing an infix expression (no spaces).
   Task:   To find the postfix equivalent of this expression.
   Return: Postfix  A string holding this postfix equivalent.
*/
void Convert(const string & Infix, string & Postfix)
{
   stack<char> OperatorStack;
   char TopSymbol, Symbol;
   int k;

   for (k = 0; k < Infix.size(); k++)
    {
     	Symbol = Infix[k];
     	 
     	if (IsOperand(Symbol))
         	Postfix = Postfix + Symbol;
         
      	else
    	{
	         while ((! OperatorStack.empty()) &&  (TakesPrecedence(OperatorStack.top(), Symbol)))
	        {
	        	TopSymbol = OperatorStack.top();
	            OperatorStack.pop();
	            Postfix = Postfix + TopSymbol;
	        }
	            
	        if ((! OperatorStack.empty()) && (Symbol == ')'))
	        	OperatorStack.pop();   	// discard matching (
	        	
	        else
	            OperatorStack.push(Symbol);
        }
    }

   while (! OperatorStack.empty())
    {
	    TopSymbol = OperatorStack.top();
	    OperatorStack.pop();
	    Postfix = Postfix + TopSymbol;
    }
}
/*---------------------------------------------
  My function needed to tokenise the expression
  --------------------------------------------*/  
      
string Change_me(string my_string)
{
    for(int i = 0; i <my_string.length(); i++)
    {
      if(isdigit(my_string[i])!=0)
      {
          if(isdigit(my_string[i+1])==0)
          {  
              my_string.insert(i+1, "v");
                            
          }    
      }    
    }

    return my_string;
}  

/*-----------------------------------------
  My function needed to tokenise expression
  -----------------------------------------*/ 
string Insert_comma(string my_string)
{
    for(int i = 0; i <my_string.length(); i++)
    {
      if ((my_string[i]=='*')||    (my_string[i]=='-')||     (my_string[i]=='/')||     (my_string[i]=='+'))
        {
            my_string.insert(i+1, ",");
        } 
        
        else if(my_string[i]=='v')
        {
            my_string.replace(i,1,",");
             
        }               
    }
    return my_string; 
}   

/*-----------------------------------------
  My function to check that no variables
  were entered
  -----------------------------------------*/ 
bool Check_valid(string my_string)
{
    string array="0123456789+-*/()";

    int count=0;
    
    for (int i=0; i<my_string.length(); i++)
    {
        for(int j=0; j<array.length(); j++)
        {
            if(my_string[i]==array[j])
            {
               count++;
            }
        }
    }
    
    if (count == my_string.length())
    {
      return true;   
    }
    else
    {   
      return false;   
    }
            
}  

/*-----------------------------------
  My function to actually evaluate
  postfix expression
  ----------------------------------*/

void Next(string my_string)
{
  vector <string> array; 
  string tempy;
  
  int comma_count=0;
  
  for (int a=0; a<my_string.length();a++)
  {
      if(my_string[a]==',')
      {
          comma_count++;
      }
  }        

  //Evaluate tokens using the "," as a delimiter
  while (my_string.find(",", 0) != string::npos)
  { 
    size_t pos = my_string.find(",", 0); 
    tempy = my_string.substr(0, pos);      
    my_string.erase(0, pos + 1);           
    array.push_back(tempy); //store in vector              
  }

  //array.push_back(my_string);//the last token is all alone 
  
  stack <string> my_stack;//initialise stack
  string temp[100];
  string ch;
  
  for (int i=0; i<comma_count; i++)
	{
	    string s;
	    s=array[i]; //make it easier to read
	      
	    if ((s!="+")&&  (s!="*")&&    (s!="-")&&   (s!="/"))
	    {
	        my_stack.push(s);
	            
	    }
	         
		else //i.e if it encounters an operator
	    {
	        my_stack.push(s);//push operator onto stack
	        temp[0]= my_stack.top();//store value
	    	my_stack.pop(); //erase from the stack
	             
	        temp[1]= my_stack.top();//store value
	        my_stack.pop();//erase from the stack
	               
	    	if (! my_stack.empty())
	        {
	            temp[2]= my_stack.top();//store value
	            my_stack.pop();//erase from the stack
	        }
	               
			else
	        {
	        
	            my_stack.push("0");
	            temp[2]= my_stack.top();
	            my_stack.pop();
	        }         
	
	        double z;
	        z = Eval(temp);
	    	ostringstream outs;  // Declare an output string stream.
	        outs << z;   // Convert value into a string.
	        ch = outs.str(); 
	
	        my_stack.push(ch);
	    }                
   }
  	cout<<ch;  
  	cin.get(); 
} 

/*------------------------------
  My function to do the math:
  Converts string to double
  then back to string
  ------------------------------*/
double Eval(string temp[])
{
    string a,b,c;
    a=temp[2]; b=temp[0]; c=temp[1];
    double x,y,z;
    istringstream ins,inse;
    ins.str(a);inse.str(c);
    ins >> x;
    inse >> y;
    
    if (b=="+")
    {
    	z = x + y;
        return z;
    } 
    
    else if (b=="-")
    {
        z = x - y;
        return z;
    }
	 
    else if (b=="*")
    {
        z = x * y;
        return z;
    }
    
    else if (b=="/")
    {
        z = x / y;
        return z;
    }                    
}

