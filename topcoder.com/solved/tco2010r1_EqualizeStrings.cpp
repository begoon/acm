#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#define __int64 long long

// abcdefghijklm
// nopqrstuvwxyz
void solve(istream& is, ostream& os) {
  string a, b;
  is >> a >> ws >> b;
  string r(a.length(), '#');
  for (int i = 0; i < a.length(); ++i) {
    int d = abs(a[i] - b[i]);
    r[i] = d < 13 ? min(a[i], b[i]) : 'a';
  }
  os << r << endl;
}

const char* liner = "--------";
int problem;
int problem_filter;

void run(int line, const char* input, const char* output) {
  problem += 1;
  if (problem_filter != -1 && problem_filter != problem) return;

  stringstream is(input);
  stringstream os;
  solve(is, os);
  if (os.str() != output) {
    cerr << "Case #" << problem << ": FAILED (line " << line << ")" << endl;
#ifdef _DEBUG
    stringstream error;
    error << __FILE__ << "(" << line << "): error: test case " << problem << " FAILED" << endl;
    OutputDebugStringA(error.str().c_str());  
#endif
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else 
    cerr << "Case #" << problem << " OK (line " << line << ")" << endl;
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

problem = -1;
problem_filter = -1;

run(__LINE__,
"cat\n"
"dog\n"
,
"caa\n"
);

run(__LINE__,
"abcdefghijklmnopqrstuvwxyz\n"
"bcdefghijklmnopqrstuvwxyza\n"
,
"abcdefghijklmnopqrstuvwxya\n"
);

run(__LINE__,
"programmingcompetitionsrule\n"
"programmingcompetitionsrule\n"
,
"programmingcompetitionsrule\n"
);

run(__LINE__,
"topcoderopen\n"
"onlinerounds\n"
,
"onlcndaoondn\n"
);

// -----------------------------------------------------------
run(__LINE__,
"cat\n"
"dog\n"
,
"caa\n"	
);

run(__LINE__,
"abcdefghijklmnopqrstuvwxyz\n"
"bcdefghijklmnopqrstuvwxyza\n"
,
"abcdefghijklmnopqrstuvwxya\n"	
);

run(__LINE__,
"programmingcompetitionsrule\n"
"programmingcompetitionsrule\n"
,
"programmingcompetitionsrule\n"	
);

run(__LINE__,
"topcoderopen\n"
"onlinerounds\n"
,
"onlcndaoondn\n"	
);

run(__LINE__,
"aazanamaobnbmbobpxxxyyyzzz\n"
"azanamaobnbmbobpbzyxzyxzyx\n"
,
"aaaaaaaaabbbbaaaaxxxyyxzyx\n"	
);

run(__LINE__,
"oxj\n"
"imo\n"
,
"imj\n"	
);

run(__LINE__,
"tdnzvghl\n"
"nvhhjmzs\n"
,
"nahajgal\n"	
);

run(__LINE__,
"gskstxncxwploxjebv\n"
"yzjaiksblsjeeomhpx\n"
,
"asjaianblsjeeojeav\n"	
);

run(__LINE__,
"zzsjzcrhulejffoajqlxyfwqevdqkhudcizcmxxfshomk\n"
"ksmjzoujccnbcazakzlhsmtfboteseqkninwqeviegumc\n"
,
"asmjzcrhacebcaoajqlasftfboaekeqdcinamavfagomc\n"	
);

run(__LINE__,
"ylygvkabtioalcsdwuotigpugjnmbkcmvbxoipwhavuvnbpke\n"
"tfwpzlgxdqkwgpfjdyxqbhfbicwlbrzsqzxmfrxqjsnhbkmtl\n"
,
"tfwgvkaaaikagaadauoqbgfagcnlbkamqaxmfpwhasnabbmke\n"	
);

run(__LINE__,
"ocfmfrgrphpuqpvubnugufprdrwqssolndeveuhjtinztffgrc\n"
"pxonbiolxlzjppbonivgllbherjsvbczglatewduemrmtxdftk\n"
,
"oafmbiglphpjppaobiuglfahdraqsacagdateudjainatadfrc\n"	
);

run(__LINE__,
"mltmv\n"
"rukyd\n"
,
"mlkma\n"	
);

run(__LINE__,
"norkqfb\n"
"pdpqvsi\n"
,
"ndpkqab\n"	
);

run(__LINE__,
"rdlaokqchxbocbmzhjtxp\n"
"oqwvqvogifvnerkaxxojs\n"
,
"oalaokochaancakaaaoap\n"	
);

run(__LINE__,
"qqyuhokxrunltnvnekbbrjtzxmuyxqwwgimkoqkcxzz\n"
"ngzpwjwajatycdmosbfqgyxlqprxidkitsaarcmrbfv\n"
,
"ngypajkajanaadmnabbagataqmrxaakaaiaaoakaaav\n"	
);

run(__LINE__,
"eolnscassggpwauarbydbfynejltrnzbgxglqdoaordsytfb\n"
"xlaxnunkssqaabzrmdvzcninvpjmclcmnrdhhybchdfxrjra\n"
,
"alannaaksggaaauambvabfanajjmalabgrdhhaaahadsrjfa\n"	
);

run(__LINE__,
"eltemmzycsgscdiqcvsyumnqktzadmvjhaznpcwffilzyakyim\n"
"wrydxbjbmtedhakjsfwafevlpvyunwklaxikdyuhvvvrdedqpi\n"
,
"altdmbaacseacaijaasaaenlktyadmkjaaakdaufaalraadqii\n"	
);

run(__LINE__,
"rzbvbk\n"
"qqwutu\n"
,
"qqauak\n"	
);

run(__LINE__,
"qsfhrjtbi\n"
"biyfknllt\n"
,
"aiafkjlbi\n"	
);

run(__LINE__,
"uhkwwiggjrbstk\n"
"tygrowkcrygrfo\n"
,
"tagroagcjrbrak\n"	
);

run(__LINE__,
"ivwoltddkdypqeyezibbjdpwfyddkacreuiphnkvnwelqy\n"
"onygtbgpxwkokycjexhsqslvwjhbyzasgihcoqfpcqrmme\n"
,
"inwgladdaaaokaaeaabajalvaadbaaareihahnfpcqalma\n"	
);

run(__LINE__,
"ftdijyhitvwpscpmarwsgtuexrxtmvlbzadqexjmagwmxful\n"
"pwdcdonjulftqjitkancxasosxcgjgkegorwcwzhpvmogqmn\n"
,
"ftdcdohitlapqcimaanaaasesraajakbaaaqcwahaammafml\n"	
);

run(__LINE__,
"qgqfcgwspdojlsieixbyimduphsovejaiwkzsngkhmvanuyrvy\n"
"xwqkizppkmaixgguyzylzcuduvosrztfrbipjjazsdiyzkpfwm\n"
,
"qaqfcappkdailggaaxaaacaapaoorajaiaipjjaahdaankpfvm\n"	
);

run(__LINE__,
"locgy\n"
"oolbn\n"
,
"locbn\n"	
);

run(__LINE__,
"qwppatznd\n"
"aghymptmc\n"
,
"aahpaptmc\n"	
);

run(__LINE__,
"tilgbbxsfrmorazhalkoquf\n"
"hubjoupujbftzibklqnwugz\n"
,
"hibgaapsfaforaahalkoqaa\n"	
);

run(__LINE__,
"edjocwejlnhifmcvchvpknwptogtfjnc\n"
"kxfffetsdaunugqcttavkucwzvlrfgec\n"
,
"eaffcaajdaaiagaaahapknaptogrfgec\n"	
);

run(__LINE__,
"cflzgaifhmyrzxqowhwvpevqerqaweesrhaxyrxpycxiujhn\n"
"vgpwrtaebzgnxdtylmweeiyrmvyqzfqyehhuhwnqfdydhvpy\n"
,
"aflwgaaebaanxaqolhwaeevqerqaweesahauarnpacxdajhn\n"	
);

run(__LINE__,
"vmetkijzbisfkhpsyapaljmzdjgjdhwuyunxquz\n"
"vvpseeaujlhthrnlysgdihudiwueochxueftiuo\n"
,
"vmeseeaubihahhnlyagaihmadaaedcauuaftiuo\n"	
);

run(__LINE__,
"a\n"
"a\n"
,
"a\n"	
);

run(__LINE__,
"a\n"
"z\n"
,
"a\n"	
);

run(__LINE__,
"b\n"
"n\n"
,
"b\n"	
);

run(__LINE__,
"o\n"
"b\n"
,
"a\n"	
);

run(__LINE__,
"b\n"
"n\n"
,
"b\n"	
);

run(__LINE__,
"jinmys\n"
"ysosru\n"
,
"ainmrs\n"	
);

run(__LINE__,
"bpanyo\n"
"zonman\n"
,
"aoaman\n"	
);

run(__LINE__,
"wzxjrusb\n"
"ihacfusz\n"
,
"aaacfusa\n"	
);

run(__LINE__,
"zyyoyann\n"
"zzpnzzzm\n"
,
"zypnyanm\n"	
);

run(__LINE__,
"uqbpjfzshdzbxyoj\n"
"azznxcwyzdhiaosw\n"
,
"aqanacwsadabaooa\n"	
);

run(__LINE__,
"zomybaaozmznmbmb\n"
"amanpznoannaoynm\n"
,
"amanaaaoamnamamb\n"	
);
run(__LINE__,
"krzyzhqiqgpqgzohvkkqhoolaohgnj\n"
"hxaixcqpkiwaaezplwbxninbvpsdvf\n"
,
"hraaxcqikgpaaaohlkbqhinbaohdnf\n"	
);

run(__LINE__,
"ynyybpazmzmbpamopooobpbyzopbmo\n"
"ybzoaabazoznponaazopopnpmbbanp\n"
,
"ybyoaaaaaoabpamaaoooapbpaaaamo\n"	
);

run(__LINE__,
"wosqiomtnygzcvcynjbixipeimyqvjbrzviijwdwwjyygaxwj\n"
"yejgtpqinhdwkwwiggrcjqzuozdowzzwfkdzatjncomnkivtq\n"
,
"wejgiominadwcvaaggacaipaiaaovaarakdaatdnajmngavtj\n"	
);

run(__LINE__,
"omznoponanomobzonyoppynmamzaaynonbzyymazypnnybyaz\n"
"mpobzzbnzbnpmzzoyynbybzmobbpabpmzboybpbaympbnppam\n"
,
"mmobopanabnmmazonynapanmabaaaanmnboyamaaymnbnapaa\n"	
);

run(__LINE__,
"apvphrdiqnudqbtebqzeonovwcudzpczfzqmqtwhismavfexvd\n"
"dlsthqydtxtywyxmmqikzsdltyrxxoddaxwjowmjtfhrfhetxo\n"
,
"alsphqadqntaqatebqaeondltaraxocaaxqjotmhiahaafetvd\n"	
);

run(__LINE__,
"nnapbbmobmpynppnopbybnonyppobnamoaaynmnmyzbaoymaoo\n"
"zpymzoapabzaoobonmaoyyozzapnbbyayomybmmbpnnbymyayy\n"
,
"nnamaaaoabpanoannmaoanonyapnbbaaoaaybmmbpnbaommaoo\n"	
);

run(__LINE__,
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
,
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"	
);

run(__LINE__,
"nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n"
"nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n"
,
"nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n"	
);

run(__LINE__,
"b\n"
"m\n"
,
"b\n"	
);

run(__LINE__,
"b\n"
"o\n"
,
"a\n"	
);

run(__LINE__,
"abcdefghijklmnopqrstuvwxyznopqrstuvwxyzabcdefghijk\n"
"nopqrstuvwxyzabcdefghijklmabcdefghijklmnopqrstuvwx\n"
,
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"	
);

run(__LINE__,
"abcdefghijklmnopqrstuvwxyzcdefghijklmnopqrstuvwxyz\n"
"zyxwwwwwwwwbbbbbcccccccccczyxwwwwwwwwbbbbbcccccccc\n"
,
"aaaaaaaaaakbbbaaaaaaaaaaaaaaaaaaaaklmbaaaaaaaaaaaa\n"	
);

run(__LINE__,
"bcde\n"
"zxvd\n"
,
"aaad\n"	
);

run(__LINE__,
"b\n"
"y\n"
,
"a\n"	
);

run(__LINE__,
"b\n"
"z\n"
,
"a\n"	
);

run(__LINE__,
"jaksdfhsdf\n"
"jhgfdljksd\n"
,
"jagadfhkad\n"	
);

run(__LINE__,
"z\n"
"c\n"
,
"a\n"	
);

run(__LINE__,
"bbbbb\n"
"nopzy\n"
,
"baaaa\n"	
);

run(__LINE__,
"c\n"
"o\n"
,
"c\n"	
);

run(__LINE__,
"z\n"
"b\n"
,
"a\n"	
);

run(__LINE__,
"ab\n"
"ac\n"
,
"ab\n"	
);

run(__LINE__,
"b\n"
"p\n"
,
"a\n"	
);

run(__LINE__,
"bboo\n"
"otch\n"
,
"aach\n"	
);

run(__LINE__,
"j\n"
"z\n"
,
"a\n"	
);

run(__LINE__,
"x\n"
"b\n"
,
"a\n"	
);

run(__LINE__,
"zzz\n"
"bbb\n"
,
"aaa\n"	
);

run(__LINE__,
"c\n"
"n\n"
,
"c\n"	
);

run(__LINE__,
"m\n"
"z\n"
,
"a\n"	
);

run(__LINE__,
"j\n"
"u\n"
,
"j\n"	
);

run(__LINE__,
"z\n"
"z\n"
,
"z\n"
);

// -----------------------------------------------------------

#ifdef _DEBUG
getchar();
#endif

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
// istream& is = cin;
// ostream& os = cout;

solve(is, os);

#endif

return 0;
}
