cplex -c "read lpex1.lp" "opt" "d sol v -"
echo ""

#g++ solve.cpp -o solve -I/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/include/ -I/opt/ibm/ILOG/CPLEX_Studio_Community128/concert/include/ -DIL_STD -L/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/lib -L/opt/ibm/ILOG/CPLEX_Studio_Community128/concert/lib 
# -lilocplex -lconcert -lcplex -lm -lpthread

#gcc -O0 -c -m64 -fPIC -fno-strict-aliasing  -I/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/include lpex1.c -o lpex1.o
#gcc -O0 -m64 -fPIC -fno-strict-aliasing  -I/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/include -L/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/lib/x86-64_linux/static_pic -o lpex1 lpex1.o -lcplex -lm -lpthread -ldl


#g++ -O0 -c -m64 -fPIC -fno-strict-aliasing  -I/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio_Community128/concert/include -L/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/lib/x86-64_linux/static_pic -L/opt/ibm/ILOG/CPLEX_Studio_Community128/concert/lib/x86-64_linux/static_pic -DIL_STD solve.cpp -o solve
#g++ -O0 -m64 -fPIC -fno-strict-aliasing  -I/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/include -I/opt/ibm/ILOG/CPLEX_Studio_Community128/concert/include/ -L/opt/ibm/ILOG/CPLEX_Studio_Community128/cplex/lib/x86-64_linux/static_pic -L/opt/ibm/ILOG/CPLEX_Studio_Community128/concert/lib/x86-64_linux/static_pic -DIL_STD -o solve solve.o -lcplex -lm -lpthread -ldl
