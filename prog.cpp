#include <iostream>
#include <fstream>

struct Candidato{
	std::string nome;
	std::string linhaArquivo;
	char respostas[10];
	int nota=0;
};

struct Questoes{
	long int acertos[10]={0,0,0,0,0,0,0,0,0,0};
	long int brancos[10]={0,0,0,0,0,0,0,0,0,0};
	int numeroQuestoes[10]={1,2,3,4,5,6,7,8,9,10}; //vetor para identificar o numero das questoes quando os vetores acertos e brancos forem ordenados
};


//============================= INICIO PROGRAMA ===========================
int main(int argc, char const *argv[]){

std::string linha;
long int quantidade=0; //total de candidatos
Candidato* lista;
Questoes questoes; //variavel usada para guardar a quantidade de acertos e brancos por questao
char gabarito[10]={'A','B','C','D','E','E','D','C','B','A'};
std::string nomeArquivo=argv[1];
std::string funcao=argv[2];
int ranking=std::atoi(argv[3]);

//RECEBER GABARITO TXT E ATRIBUIR NO VETOR GABARITO (SE FOR O CASO)=========
if(argv[4]!=NULL){
	std::string nomeGabarito=argv[4];
	std::ifstream arquivo3(nomeGabarito);
	if(arquivo3.is_open()){
		for(int i=0;i<10;i++){
			arquivo3>>gabarito[i];
		}
	}else{
		std::cout<<"Erro ao abrir arquivo\n";
	}
}

//==========================================================================

//LEITURA DO ARQUIVO E CONTAGEM DE LINHAS ==================================
std::ifstream arquivo (nomeArquivo); 
if(arquivo.is_open()){
	while(getline (arquivo,linha)){
		//std::cout << linha << '\n';
		quantidade +=1; //quantidade é o total de candidatos no concurso
	}
	arquivo.close();
}else{
	std::cout<<"Erro ao abrir arquivo\n";
} 
//==========================================================================

lista=new Candidato[quantidade];

//ATRIBUICAO DOS DADOS DO ARQUIVO TXT NAS VARIAVEIS ========================
std::ifstream arquivo2 (nomeArquivo);

if(arquivo2.is_open()){
	for(long int i=0;i<quantidade;i++){
		arquivo2>>lista[i].nome;
		//std::cout<<lista[i].nome<<"\n";
		for(int j=0;j<10;j++){
			arquivo2>>lista[i].respostas[j];
			//std::cout<<lista[i].respostas[j]<<"\n";
		}
	}
}else{
	std::cout<<"Erro ao abrir arquivo\n";
}
//=========================================================================

//CALCULO DAS NOTAS DOS ALUNOS; BRANCOS E ACERTOS POR QUESTAO =============
for(long int i=0;i<quantidade;i++){
	for(int j=0;j<10;j++){
		if(lista[i].respostas[j]==gabarito[j]){
			lista[i].nota +=1; //incrementa nota do aluno
		}
		if(lista[i].respostas[j]!='A' && lista[i].respostas[j]!='B' && lista[i].respostas[j]!='C' && lista[i].respostas[j]!='D' && lista[i].respostas[j]!='E'){
			questoes.brancos[j] +=1; //incrementa brancos por questao
		}
		if(lista[i].respostas[j]==gabarito[j]){
			questoes.acertos[j] +=1; //incrementa acertos por questao
		}
	}std::cout<<lista[i].nome<<" nota "<<lista[i].nota<<"\n";
}
//==========================================================================

//IMPRIMIR TOTAL DE BRANCOS E ACERTOS POR QUESTAO ==========================
std::cout<<"brancos ";
for(int i=0;i<10;i++){
	std::cout<<questoes.brancos[i]<<" ";
}
std::cout<<std::endl;
std::cout<<"acertos ";
for(int i=0;i<10;i++){
	std::cout<<questoes.acertos[i]<<" ";
}
//==========================================================================
std::cout<<std::endl;

//LISTAR RANKING DOS MELHORES/PIORES ALUNOS ================================
if(funcao=="best" || funcao=="worst"){
   	for(long int i=0;i<quantidade-1;i++){
    	int min=i;
    	for(long int j=i+1;j<quantidade;j++){
    		if(lista[min].nota>lista[j].nota){
    			min=j;
    		}	
    	}								//SELECTION SORT (ordem crescente)
    Candidato temp=lista[i];
    lista[i]=lista[min];
    lista[min]=temp;    	
	}
	if(funcao=="best"){ //imprime melhores (do fim do vetor para inicio)
		for(long int i=quantidade-1;i>=quantidade-ranking;i--){
			std::cout<<lista[i].nome<<"\n";
		}
	}
	if(funcao=="worst"){ //imprime piores (do inicio do vetor para fim)
		for(long int i=0;i<ranking;i++){
			std::cout<<lista[i].nome<<"\n";
		}	
	}
}
//==========================================================================

//LISTAR QUESTOES MAIS BRANCOS =============================================
if(funcao=="blank-questions"){
	for(int i=0;i<9;i++){
    	int min=i;
    	for(int j=i+1;j<10;j++){
    		if(questoes.brancos[min]>questoes.brancos[j]){
    			min=j;
    		}	
    	}								//SELECTION SORT (ordem crescente)
    long int temp=questoes.brancos[i];
    questoes.brancos[i]=questoes.brancos[min];
    questoes.brancos[min]=temp;     	
	
	int temp2=questoes.numeroQuestoes[i]; //vetor com o numero das questoes é ordenado conforme vetor de quantidade de brancos
    questoes.numeroQuestoes[i]=questoes.numeroQuestoes[min];
    questoes.numeroQuestoes[min]=temp2;     	
	}// ok daqui pra cima ===========

	for(int i=0;i<9;i++){ //===== ordenando resultado anterior pelo numero da questao (as que tem valores iguais)
		int min=i;
		for(int j=i+1;j<10;j++){
			if(questoes.brancos[min]==questoes.brancos[j] && questoes.numeroQuestoes[min]<questoes.numeroQuestoes[j]){
				min=j;
			}
		}
	int temp3=questoes.numeroQuestoes[i]; 
    questoes.numeroQuestoes[i]=questoes.numeroQuestoes[min];
    questoes.numeroQuestoes[min]=temp3; 	
	} //======

	for(int i=9;i>9-ranking;i--){ //impressao OK de brancos
 		std::cout<<questoes.numeroQuestoes[i]<<"\n";
	}
}
//==========================================================================

//LISTAR QUESTOES COM MAIS/MENOS ACERTOS ===================================
if(funcao=="best-questions" || funcao=="worst-questions"){
	for(int i=0;i<9;i++){
    	int min=i;
    	for(int j=i+1;j<10;j++){
    		if(questoes.acertos[min]>questoes.acertos[j]){
    			min=j;
    		}	
    	}								//SELECTION SORT (ordem crescente)
    long int temp=questoes.acertos[i];
    questoes.acertos[i]=questoes.acertos[min];
    questoes.acertos[min]=temp;     	
	
	int temp2=questoes.numeroQuestoes[i]; //vetor com o numero das questoes é ordenado conforme vetor com quantidade de acertos
    questoes.numeroQuestoes[i]=questoes.numeroQuestoes[min];
    questoes.numeroQuestoes[min]=temp2;     	
	}// ok daqui pra cima =================================

	for(int i=0;i<9;i++){ //===== ordenando resultado anterior pelo numero da questao (as que tem valores iguais)
		int min=i;
		for(int j=i+1;j<10;j++){
			if(questoes.acertos[min]==questoes.acertos[j] && questoes.numeroQuestoes[min]<questoes.numeroQuestoes[j]){
				min=j;
			}
		}
	int temp4=questoes.numeroQuestoes[i]; 
    questoes.numeroQuestoes[i]=questoes.numeroQuestoes[min];
    questoes.numeroQuestoes[min]=temp4; 	
	} //======

	if(funcao=="best-questions"){ //imprime questoes com mais acertos (do fim do vetor para inicio)
		for(int i=9;i>9-ranking;i--){
			std::cout<<questoes.numeroQuestoes[i]<<"\n";
		}
	}
	if(funcao=="worst-questions"){ //imprime questoes com menos acertos (do inicio do vetor para fim)
		for(int i=0;i<ranking;i++){
			std::cout<<questoes.numeroQuestoes[i]<<"\n";
		}
	}

}

//==========================================================================


//IMPRESSAO DE ALGUMAS VARIAVEIS ===========================================
std::cout<<std::endl;
std::cout<<"quantidade de candidatos "<<quantidade<<std::endl;
std::cout<<"nome do arquivo "<<nomeArquivo<<std::endl;;
std::cout<<"nome da funcao "<<funcao<<std::endl;
std::cout<<"ranking "<<ranking<<std::endl;
if(argv[4]!=NULL){
	std::cout<<"com arquivo gabarito txt"<<std::endl;
}else{
	std::cout<<"sem arquivo gabarito txt"<<std::endl;
}
std::cout<<"gabarito ";
for(int i=0;i<10;i++){
	std::cout<<gabarito[i]<<" ";	
}
std::cout<<std::endl;
std::cout<<"fim teste"<<std::endl;
//==========================================================================

delete[] lista;
return 0;
}