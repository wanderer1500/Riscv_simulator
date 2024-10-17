#include<bits/stdc++.h>
using namespace std;
vector<string> assembly;
class Register{
    public:
    string regName;
    int regNo;
    string regNo_bin;
    Register(string name){
        this->regName=name;
        regNo=stoi(regName.substr(1,regName.length()));
        regNo_in_bin();
    }
    private:
   void regNo_in_bin(){
        bitset<5> num(regNo);
        regNo_bin=num.to_string();
    }
    
    
};
/*****************************************************/
 class Immediate{
     public:
     string hexNo;
     string hex_to_bin;
     string imm7bits;
     string imm5bits;
     string jump;
     string upImbits;
     
     Immediate(string hex){
         this->hexNo=hex;
         hexTobin(hex);
         hexTobin_5bit();
         hexTobin_7bit();
         upperIm();
         
     }
     private:
     void hexTobin(string hex){
         string ans="";
         /*map for hex to binary conversion*/
           map<char,string> mp={
           {'1',"0001"},{'2',"0010"},{'3',"0011"},{'4',"0100"},
           {'5',"0101"},{'6',"0110"},{'7',"0111"},{'8',"1000"},
           {'9',"1001"},{'A',"1010"},{'B',"1011"},{'C',"1100"},
           {'D',"1101"},{'E',"1110"},{'F',"1111"}
           };
           for(int i=2;i<hex.size();i++){
               ans+=mp[hex[i]];
              
               
           }
            bitset<12> bits(ans);// 12 bits
               bitset<20> bits_lui(ans);//upper immediate and j type
               this->jump=bits_lui.to_string();
               this->hex_to_bin=bits.to_string();
               this->upImbits=bits_lui.to_string();
         
     }
     void hexTobin_7bit(){
         this->imm7bits=hex_to_bin.substr(0,7);
         
     }
     void hexTobin_5bit(){
         this->imm5bits=hex_to_bin.substr(7,5);
     }
     void upperIm(){
         while(upImbits.size()!=32){
             upImbits=upImbits+'0';
         }
     }
   
 };
 /*S type*/
 class Stype_instruction{
     public:
     string imm;
     string rs2;
     string rs1;
     string func3;
     string opcode;
     Stype_instruction(string opcode,string rs2,string rs1,string func3,string imm){
         this->imm=imm;
         this->rs1=rs1;
         this->rs2=rs2;
         this->opcode=opcode;
         this->func3=func3;
     }
     string Stype_to_binary(){
         Register Rs1(rs1);
         Register Rs2(rs2);
         Immediate Imm(imm);
         string ans=Imm.imm7bits+Rs2.regNo_bin+Rs1.regNo_bin+func3+Imm.imm5bits+opcode;
         return ans;
     }
 };
 /*R type*/
 class Btype_instruction{
     public:
     string opcode;
     string rs1;
     string rs2;
     string imm;
     string func3;
     
     Btype_instruction(string opcode,string rs1,string rs2,string imm,string func3){
         this->opcode=opcode;
         this->rs1=rs1;
         this->rs2=rs2;
         this->imm=imm;
         this->func3=func3;
     }
     string Btype_to_binary(){
         Register Rs1(rs1);
         Register Rs2(rs2);
         Immediate Im(imm);
         string ans=Im.imm7bits+Rs2.regNo_bin+Rs1.regNo_bin+func3+Im.imm5bits+opcode;
         return ans;
         
     }
 };
 /* L type*/
 class Ltype_instruction{
     public:
     string opcode;
     string rs1;
     string rd;
     string imm;
     string func3;
     Ltype_instruction(string opcode,string rs1,string rd,string imm,string func3){
         this->opcode=opcode;
         this->rs1=rs1;
         this->rd=rd;
         this->imm=imm;
         this->func3=func3;
     }
     
     string Ltype_to_binary(){
          Register Rs1(rs1);
         Register Rd(rd);
         Immediate Im(imm);
         string ans=Im.hex_to_bin+Rs1.regNo_bin+func3+Rd.regNo_bin+opcode;
         return ans;
     }
 };
 /*I type */
class Itype_instruction{
    public:
    string opcode;
    string rs1;
    string imm;
    string rd;
    string func3;
    string func7;
    Itype_instruction(string opcode,string rs1,string imm,string rd,string func3,string func7){
        this->opcode=opcode;
        this->rs1=rs1;
        this->imm=imm;
        this->rd=rd;
        this->func3=func3;
        this->func7=func7;
    }
    string Itype_to_binary(){
          Register Rs1(rs1);
         Register Rd(rd);
         Immediate Im(imm);
         string ans=Im.hex_to_bin+Rs1.regNo_bin+func3+Rd.regNo_bin+opcode;
         return ans;
    }
    string IRtype_to_binary(){
          Register Rs1(rs1);
         Register Rd(rd);
         Immediate Im(imm);
         string ans=func7+Im.imm5bits+Rs1.regNo_bin+func3+Rd.regNo_bin+opcode;
         return ans;
    }
};
/*R type*/
class Rtype_instruction{
    public:
    string opcode;
    string rs1;
    string rs2;
    string rd;
    string func3;
    string func7;
    Rtype_instruction(string opcode,string rs1,string rs2,string rd,string func3,string func7){
        this->opcode=opcode;
        this->rs1=rs1;
        this->rs2=rs2;
        this->rd=rd;
        this->func3=func3;
        this->func7=func7;
    }
    string Rtype_to_binary(){
        Register Rd(rd);
        Register Rs1(rs1);
        Register Rs2(rs2);
        string ans="";
        ans=func7+Rs2.regNo_bin+Rs1.regNo_bin+func3+Rd.regNo_bin+opcode;
        return ans;
    }
};
class Jtype_instruction{
    public:
    string rd;
    string rs1;
    string opcode;
    string func3;
    string imm;
Jtype_instruction(string opcode,string rs1,string rd,string imm,string func3){


this->rs1=rs1;
this->rd=rd;
this->opcode=opcode;
this->imm=imm;
this->func3=func3;
}
string Jtype_to_binary(){
    Register Rd(rd);
    Immediate Im(imm);
    string ans=Im.jump+Rd.regNo_bin+opcode;
    return ans;
}
string JL_type_to_binary(){
    Register Rd(rd);
    Register Rs1(rs1);
    Immediate Im(imm);
    string ans=Im.hex_to_bin+Rs1.regNo_bin+func3+Rd.regNo_bin+opcode;
    return ans;
}

};
    
    class Instruction_Convertor{
        public:
        map<string,vector<string>> instruction_map={
            {"ADD",{"R","000","0000000"}},
            {"SUB",{"R","000","0100000"}},
            {"AND",{"R","111","0000000"}},
            {"OR",{"R","110","0000000"}},
             {"XOR",{"R","100","0000000"}},
             {"SLL",{"R","001","0000000"}},
             {"SRL",{"R","101","0100000"}},
             {"SLT",{"R","010","0000000"}},
             {"SLTU",{"R","011","0000000"}},
             {"ADDI",{"I","000",""}},
            {"SLLI",{"IL","001","0000000"}},
            {"SLTI",{"IL","010","0000000"}},
            {"SLLTU",{"IL","011","0000000"}},
             {"XORI",{"I","100",""}},
             {"SRLI",{"IR","101","0100000"}},
            {"SRAI",{"IR","101","0100000"}},
             {"ORI",{"I","110",""}},
             {"ANDI",{"I","111",""}},
             {"LB",{"L","000",""}},
              {"LH",{"L","001",""}},
               {"LW",{"L","010",""}},
               {"LBU",{"L","100",""}},
               {"LHU",{"L","101",""}},
               {"BEQ",{"B","000",""}},
               {"BNE",{"B","001",""}},
               {"BLT",{"B","100",""}},
               {"BGE",{"B","101",""}},
               {"SB",{"S","000",""}},
               {"SH",{"S","001",""}},
               {"SW",{"S","010",""}},
               {"SD",{"S","011",""}},
               {"JAL",{"J","",""}},
               {"JALR",{"JL","000",""}}
               
               
              
        };
        map<string,string> opCode_from_Type={
            {"R","0110011"},
            {"I","0010011"},
            {"IL","0010011"},
            {"IR","0010011"},
            {"L","0000011"},
            {"B","1100011"},
            {"S","0100011"},
            {"J","1101111"},
            {"JL","1100111"}
            
            
            
        };
        string conversion(string s){
            stringstream ss(s);
            string opCode;
            ss>>opCode;
            if(instruction_map.find(opCode)==instruction_map.end()){
                return "Invalid";
            }
            string type=instruction_map[opCode][0];
            string func3=instruction_map[opCode][1];
            string func7=instruction_map[opCode][2];
            if(type=="S"){
                opCode=opCode_from_Type[type];
                string rs2,temp,imm,rs1;
                imm="";
                rs1="";
                ss>>rs2>>temp;
                rs2.pop_back();
                int ind=-1;
                for(int i=0;i<temp.size();i++){
                    if(temp[i]=='['){
                        ind=i;
                        break;
                    }
                    imm+=temp[i];
                }
                rs1=temp.substr(ind+1,temp.length());
                rs1.pop_back();
                Stype_instruction S1(opCode,rs2,rs1,func3,imm);
                string ans=S1.Stype_to_binary();
                return ans;
            }else if(type=="B"){
                 opCode=opCode_from_Type[type];
                string rs2,imm,rs1;
                ss>>rs1>>rs2>>imm;
                rs1.pop_back();
                rs2.pop_back();
                Btype_instruction B1(opCode,rs1,rs2,imm,func3);
                string ans=B1.Btype_to_binary();
                return ans;
            }else if(type=="L"){
                 opCode=opCode_from_Type[type];
                string rd,temp;
                ss>>rd>>temp;
               string rs1,imm;
               imm="";
                 int ind=-1;
                for(int i=0;i<temp.size();i++){
                    if(temp[i]=='['){
                        ind=i;
                        break;
                    }
                    imm+=temp[i];
                }
                 rs1=temp.substr(ind+1,temp.length());
                rs1.pop_back();
                Ltype_instruction L1(opCode,rs1,rd,imm,func3);
                string ans=L1.Ltype_to_binary();
                return ans;
            }else if(type=="IR"){
                string rd,rs1,imm;
                ss>>rd>>rs1>>imm;
                rd.pop_back();
                rs1.pop_back();
                opCode=opCode_from_Type[type];
                Itype_instruction I1(opCode,rs1,imm,rd,func3,func7);
               
                string ans=I1.IRtype_to_binary();
                return ans;
            }else if(type=="I"){
                string rd,rs1,imm;
                ss>>rd>>rs1>>imm;
                rd.pop_back();
                rs1.pop_back();
                opCode=opCode_from_Type[type];
                Itype_instruction I1(opCode,rs1,imm,rd,func3,func7);
                
                string ans=I1.Itype_to_binary();
                return ans;
            }else if(type=="R"){
                  string rs1,rs2,rd;
                ss>>rd>>rs1>>rs2;
                rd.pop_back();
                rs1.pop_back();
                 opCode=opCode_from_Type[type];
                Rtype_instruction R1(opCode,rs1,rs2,rd,func3,func7);
               
                string ans=R1.Rtype_to_binary();
                return ans;
            }else if(type=="J"){
                string rd,imm;
                ss>>rd>>imm;
                rd.pop_back();
                opCode=opCode_from_Type[type];
                Jtype_instruction J_Type(opCode,"",rd,imm,func3);
                return J_Type.Jtype_to_binary();
            }else if(type=="JL"){
                string rd,rs1,imm;
                ss>>rd>>rs1>>imm;
                rd.pop_back();
                rs1.pop_back();
                opCode=opCode_from_Type[type];
                Jtype_instruction J_Type(opCode,rd,func3,rs1,imm);
                return J_Type.Jtype_to_binary();
            }
           return "Invalid"; 
        }
        
        
        
    };
    
  /*********************/
  class StringParser{
      public:
      string str="";
      StringParser(string syntax){
          this->str=syntax;
      }
      vector<string> convertor(){
          string to_machine_code="";
          vector<string> vec;
          
          for(auto s:str){
              if(s==';'){
                  Instruction_Convertor C1;
                //   cout<<C1.conversion(to_machine_code)<<"\n";
                  vec.push_back(C1.conversion(to_machine_code));
                  assembly.push_back(to_machine_code);
                  to_machine_code="";
              }else{
                  to_machine_code+=s;
              }
          }
          return vec;
      }
  };
    



int main(){
    // string ans=regTobin("R10");
    // cout<<ans<<"\n";
    string s1="ADD x1, x2, x3;";
    StringParser p(s1);
    vector<string> m=p.convertor();
    for(auto str:assembly){
        for(auto c:str){
            cout<<c;
        }
        cout<<"\n";
    }
     for(auto str:m){
        for(auto c:str){
            cout<<c;
        }
        cout<<"\n";
    }
    assembly.clear();
    
    
}