import java.util.Stack;
import java.util.Scanner;
import java.io.*;

public class LL
{
    public String input = "";
    private int indexOfInput = -1;
    int res = 0;

    Stack <String> stck = new Stack<String>();

    String[][] table =
            {
                    {"dm(){C}",null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,"sync"},
                    {"DL",null,null,null,null,"DL",null,null,null,null,null,"DL",null,null,null,null,null},
                    {"dV",null,null,null,null,"",null,null,null,null,null,"",null,null,null,null,null},
                    {null,null,null,null,null,"sync","iW",null,null,null,null,"sync",null,null,null,null,null},
                    {null,null,null,null,null,"sync",null,";","=n,V",null,",V","sync",null,null,null,null,null},
                    {null,null,null,null,null,"",null,null,null,null,null,"k(X){B}",null,null,null,null,null,},
                    {null,null,null,"sync",null,null,"TOT",null,null,"TOT",null,null,"b",null,null,null,null},
                    {null,null,null,"sync",null,null,"i",null,"sync","n",null,null,null,"sync","sync",null,null},
                    {null,null,null,null,null,null,"sync",null,"==","sync",null,null,null,"<P",">Q",null,null},
                    {null,null,null,null,null,null,"",null,"=","",null,null,null,null,null,null,null},
                    {null,null,null,null,null,null,"",null,"=","",null,null,null,null,null,null,null},
                    {null,null,null,null,null,"sync","i=i+i;",null,null,null,null,null,null,null,null,null,null}
            };

    String[] nonTerm = {"S","C","D","V","W","L","X","T","O","P","Q","B"};
    String[] term = {"d","m","(",")","{","}","i",";","=","n",",","k","b","<",">","+","$"};

    public LL(String in)
    {
        this.input = in;
    }

    private void push(String s){this.stck.push(s);}
    private String pop(){return this.stck.pop();}

    public void algorithm()
    {
        push("$");
        push("S");

        String token = read();
        String top = null;

        System.out.println(stck);
        top = this.pop();

        do {

            if(isNonTerminal(top))
            {
                String rule = this.getRule(top,token);
                if(rule.equals("sync"))
                {
                    res = 1;
                    if(top.equals(("S")))
                    {
                        token = read();
                    }
                    else
                    {
                        top = this.pop();
                        System.out.println(stck);
                    }
                }
                else if(rule.equals("skip"))
                {
                    res = 1;
                    token = read();
                }
                else if(!rule.equals(""))
                {
                    this.pushRule(rule);
                    System.out.println(stck);
                    top = this.pop();
                }
                else
                {
                    top = this.pop();
                }

            }
            else if(isTerminal(top))
            {
                if(top.equals("$"))
                {
                    break;
                }

                if(!top.equals(token))
                {
                    res = 1;
                    error("Token and top of stack dont match for terminal.");
                    top = this.pop();
                    System.out.println(stck);
                }
                else
                {
                    System.out.println("Matched token "+token);
                    System.out.println(stck);
                    token = read();
                    top = this.pop();
                }
            }

        }while(true);

        if(token.equals(top))
        {
            if(res == 0)
                System.out.println("Input accepted with no errors.");
            else
                System.out.println("Input accepted with errors.");
        }
        else
            System.out.println("Input not accepted.");

    }

    private String read()
    {
        indexOfInput++;
        char ch = this.input.charAt(indexOfInput);
        String str = String.valueOf(ch);
        return str;
    }

    private boolean isTerminal(String s)
    {
        for(int i=0;i<this.term.length;i++)
        {
            if(s.equals(this.term[i]))
                return true;
        }
        return false;
    }

    private boolean isNonTerminal(String s)
    {
        for(int i=0;i<this.nonTerm.length;i++)
        {
            if (s.equals(this.nonTerm[i]))
                return true;
        }
        return false;
    }

    public String getRule(String nonTerm,String term)
    {
        int row = getNonTermIndex(nonTerm);
        int col = getTermIndex(term);
        String rule = this.table[row][col];
        if(rule == null)
        {
            error("No entry in table");
            return "skip";
        }
        return rule;
    }

    private int getNonTermIndex(String s)
    {
        for(int i=0;i<this.nonTerm.length;i++)
        {
            if(s.equals(this.nonTerm[i]))
                return i;
        }
        return -1;
    }

    private int getTermIndex(String s)
    {
        for(int i=0;i<this.term.length;i++)
        {
            if(s.equals(this.term[i]))
                return i;
        }
        return -1;
    }

    private void error(String mssg)
    {
        System.out.println(mssg);
    }

    private void pushRule(String rule)
    {
        for(int i=rule.length()-1;i>=0;i--)
        {
            char ch = rule.charAt(i);
            String str = String.valueOf(ch);
            push(str);
        }
    }

    public static void main(String args[]) throws IOException
    {
        Scanner file = new Scanner(new File("tokens.txt"));
        String tokens = file.nextLine();
        LL parser = new LL(tokens+"$");
        parser.algorithm();
    }
}