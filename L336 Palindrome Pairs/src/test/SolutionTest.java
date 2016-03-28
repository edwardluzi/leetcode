import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

import org.junit.Test;

public class SolutionTest
{
	private Comparator<Integer[]> comparator = new Comparator<Integer[]>()
	{
		@Override
		public int compare(Integer[] o1, Integer[] o2)
		{
			boolean empty1 = o1 == null || o1.length == 0;
			boolean empty2 = o2 == null || o2.length == 0;

			if (empty1 && empty2)
			{
				return 0;
			}
			else if (empty1)
			{
				return -1;
			}
			else if (empty2)
			{
				return 1;
			}
			else
			{
				int index = 0;

				for (; index < o1.length && index < o2.length; index++)
				{
					int c = o1[index] - o2[index];

					if (c != 0)
					{
						return c;
					}
				}

				if (o1.length == o2.length)
				{
					return 0;
				}
				else
				{
					return o1.length > o2.length ? 1 : -1;
				}
			}
		}
	};

	@Test
	public void test1()
	{
		Integer[][] expected = new Integer[][] { { 1, 0 }, { 0, 1 } };
		String[] words = { "bat", "tab", "cat" };
		Solution solution = new Solution();
		List<List<Integer>> result = solution.palindromePairs(words);
		Arrays.sort(expected, this.comparator);
		assertTrue(Arrays.deepEquals(expected, convert(result)));
	}

	@Test
	public void test2()
	{
		Integer[][] expected = new Integer[][] { { 0, 1 }, { 1, 0 }, { 3, 2 }, { 2, 4 } };
		String[] words = { "abcd", "dcba", "lls", "s", "sssll" };
		Solution solution = new Solution();
		List<List<Integer>> result = solution.palindromePairs(words);
		Arrays.sort(expected, this.comparator);
		assertTrue(Arrays.deepEquals(expected, convert(result)));
	}

	@Test
	public void test3()
	{
		Integer[][] expected = new Integer[][] { { 0, 1 }, { 1, 0 } };
		String[] words = { "a", "" };
		Solution solution = new Solution();
		List<List<Integer>> result = solution.palindromePairs(words);
		Arrays.sort(expected, this.comparator);
		assertTrue(Arrays.deepEquals(expected, convert(result)));
	}

	@Test
	public void test4()
	{
		Integer[][] expected = new Integer[][] { { 3, 0 }, { 1, 3 }, { 4, 0 }, { 2, 4 }, { 5, 0 }, { 0, 5 } };
		String[] words = { "a", "b", "c", "ab", "ac", "aa" };
		Solution solution = new Solution();
		List<List<Integer>> result = solution.palindromePairs(words);
		Arrays.sort(expected, this.comparator);
		assertTrue(Arrays.deepEquals(expected, convert(result)));
	}

	@Test
	public void test5()
	{
		Integer[][] expected = new Integer[][] { { 152, 7 }, { 142, 15 }, { 15, 17 }, { 310, 21 }, { 396, 37 },
				{ 289, 37 }, { 320, 37 }, { 367, 37 }, { 64, 41 }, { 155, 41 }, { 136, 42 }, { 37, 43 }, { 258, 51 },
				{ 540, 51 }, { 41, 51 }, { 475, 51 }, { 91, 51 }, { 361, 51 }, { 127, 51 }, { 282, 64 }, { 155, 64 },
				{ 311, 64 }, { 83, 64 }, { 142, 83 }, { 142, 91 }, { 161, 99 }, { 156, 100 }, { 431, 100 },
				{ 316, 106 }, { 218, 120 }, { 156, 127 }, { 372, 133 }, { 460, 136 }, { 365, 136 }, { 509, 136 },
				{ 37, 137 }, { 389, 137 }, { 385, 142 }, { 497, 142 }, { 51, 155 }, { 41, 155 }, { 421, 156 },
				{ 42, 156 }, { 431, 156 }, { 186, 156 }, { 218, 156 }, { 37, 159 }, { 137, 161 }, { 266, 161 },
				{ 413, 161 }, { 415, 161 }, { 99, 161 }, { 15, 195 }, { 21, 195 }, { 277, 195 }, { 43, 195 },
				{ 325, 195 }, { 314, 211 }, { 37, 218 }, { 320, 218 }, { 21, 251 }, { 258, 253 }, { 37, 258 },
				{ 396, 258 }, { 136, 266 }, { 120, 277 }, { 161, 282 }, { 106, 282 }, { 559, 282 }, { 64, 289 },
				{ 556, 310 }, { 492, 310 }, { 195, 311 }, { 156, 320 }, { 218, 320 }, { 120, 320 }, { 136, 325 },
				{ 133, 325 }, { 100, 335 }, { 195, 361 }, { 37, 367 }, { 161, 385 }, { 33, 385 }, { 51, 396 },
				{ 258, 396 }, { 430, 396 }, { 335, 413 }, { 460, 414 }, { 51, 415 }, { 232, 415 }, { 64, 417 },
				{ 310, 421 }, { 258, 430 }, { 100, 446 }, { 37, 460 }, { 335, 475 }, { 51, 492 }, { 142, 497 },
				{ 335, 509 }, { 99, 556 } };
		
		String[] words = { "hijajcd", "hjhgahbcegj", "fjbjfecjgfjdbbgdadcb", "did", "cgjhfafgea", "chdbicgcij",
				"jiebc", "aajaaed", "afddjhg", "hiabij", "hfgidgegedeafc", "ifedfcaahhbc", "fci", "jbadcfghehiecbgjcg",
				"gihedfiabhdjicaea", "ji", "hgacdbeadahceag", "hij", "fhheadbjb", "gieghcacfccfadijcdbg", "dbeabaafia",
				"je", "ebieia", "becjedbdadecfafi", "acbchfigbiaafechfeii", "fddfbb", "jefdihii", "cfcifihdfgcjadbeec",
				"jbcfgdhifjgdgcccggfe", "ibhj", "iihihigj", "jifbhdgffiaii", "gdcgdabdhbdh", "giaa",
				"fgaidgcbgbagjjgcja", "becgcgjbeegebb", "jadgeej", "h", "fddgcbgahhh", "gecajfjcheha", "gaeejd", "bc",
				"fd", "jh", "jddecghbjaedgeadieej", "ehi", "cfijccggfeijfc", "jbdaeaeigbedebaabdg", "hjiijifigbhae",
				"aeihbbfdgfhi", "bibhjdgdejjfgd", "b", "dgfhcbgfifchhihg", "faaefigafd", "fijbabeifgjcefeffdgc",
				"ahdaiejbhegaha", "difcfcbcfg", "abdffeifcb", "ggeaej", "hbcicchejbecidi", "ijedjfcjahhajc",
				"jfacgfijbdehg", "dfbhhbdafcfhjffbcij", "cddjdgefdjbhccgaeb", "c", "gajfibiaehichfhfh", "cheegj",
				"icjhhcigfeedg", "dggf", "ificjhaihgicbhagjjgc", "ifbjbadgcccacjcaea", "biaafggehahijagj", "dghehgccj",
				"ccigbcajbb", "fgafdfhagi", "jdifdcj", "haagafjfa", "cdjibbfgije", "jgbgdcgaabeicfadedjg",
				"iahehcjhjecbjdehd", "acahgc", "ejggbffeea", "ebacgded", "ci", "igggjhfgcjfeagaed", "jjifjgfefgjgafdc",
				"ddiefahhfeifggj", "jggjfacda", "dig", "bajbghfecjajdhfebi", "bfjcbiceefafhbc", "bi", "cdaj", "bfedf",
				"affdcjd", "ebjceefjji", "cgedidfdaj", "diagcdjgcidcaabdec", "biajbeajggcaadb", "gg", "af",
				"ddeibadahhhbcgbb", "fbgjaedfgah", "fhagi", "dbggfjbhefcg", "dfgdhjcecbhjffhhcc", "gcg",
				"ibejfeehbfhbcceagbf", "beefhdiiaajbbid", "fcbgeeaggcehjagfbec", "cehgbhhdjdabjhgbdf", "ibjchciabig",
				"fjfhbdhbdchacfi", "dgaiffdjjfhihheajda", "afbdfijbaacechfeehai", "bhccifjcigdge", "ghdibjdih",
				"fhjiaja", "fadfaea", "ghhdicafbdgbccahb", "fhf", "jhfg", "jehedbbcidgahjhefj", "jdigdea",
				"acfiiaebjfeea", "eibciijib", "fghhghdhb", "bf", "jgdbcciehebec", "cbef", "ccdcegbejhcdhbjgd",
				"dacefieigggddd", "icjfbhabjjaehgic", "dja", "egidaegjegceied", "eifggahef", "d", "gh",
				"aabhihfhbjjgaaaaaaf", "hhfjgcd", "efcejjcgbhdicghbcbda", "jeecggeaidcdfeae", "i", "ddibebgcibi",
				"gcffcijafghehgffijbj", "ieb", "hhbfcdgeicihcbcgje", "aegbdaeedadig", "jjhfgeijciji", "ecjijiahfcbcf",
				"hibddjjgifbf", "eccaajecechb", "deaaj", "ecgfaaigjce", "jhhejciejdhh", "cb", "f", "cjddcfdihddechegg",
				"cgdfdbficba", "jajh", "hcfadbghjbicbachah", "g", "fhchedhbcigeci", "ghbbcijcbgeccbebaa", "chgdgjiac",
				"adfgjbbhfbdbheebhgb", "gbbebiaijhagcjfgjda", "aadhgcfjhcjaa", "fhdbhccfccajfheiaaj", "ijgjfc",
				"dcdcfaebjhgafh", "egadegbjabjgjhdbhcfb", "hhaeabfcfcjc", "gfjcijhbbie", "icgihfcgd", "gfaihjbcb",
				"hae", "ciiaefdegffchagaccj", "dbadejehhgjjfd", "abfbfdaaebhgbadf", "gfeijf", "acidgfeccdaccc",
				"chhicfj", "aejjeejbjcebd", "bcchhd", "aajideccdfgfdee", "fdd", "idabig", "bfgigiacibhibfc",
				"ghjidfcjdbfagbgg", "jdgefifgfg", "figabdib", "ieegjbjaaaheieccfifj", "hhifigebihbec", "abfdca", "j",
				"dfecghggj", "fbdg", "aghigddeagaj", "hjghddg", "biededhjegi", "aed", "jcgbbhiacef", "hgbhaadhe",
				"bjffahgjibfjijjcah", "abjgacciihhigafe", "bhighdhjgb", "idjbedcbcghfhgdjgd", "fdcge",
				"jiefciajfacejcbhiijb", "gghchaac", "jdh", "ccdabajaihbigbfbi", "edcchgggdajibbafag", "fiihgiebhhb",
				"ggbhhfjfa", "gechicejjgbebe", "fdadccghiadhgeecfeb", "fh", "gbddbi", "acjcafggc", "chgbfjfdghjfgaje",
				"fgdcfffcabdbih", "ffggdfd", "eeibfggddgbb", "bcccgbihhhaa", "ecegdgdaieicfffebd", "heig",
				"aeafdijcgffhaagajbc", "cdfecjaabhajjcag", "jgacggaabdidjgg", "hfcdjddbchagfa", "bgh", "bbiefehhfc",
				"dfhic", "checjfabdceddfefa", "bbiebgigjg", "hdchejdjeecc", "cieafdi", "bjbebfjbb", "jeeghjiaagdf",
				"ibbjgh", "jgfje", "gddfb", "iadhbabgjjci", "faafifgeddfcaji", "ijejbiidaefibga", "gjhdgffcebfdbbhh",
				"hfbccbbbhebgjihfbhad", "jhjeffebgiaijecihcbh", "bdacgdeeiajehjhd", "cej", "fbbhabbdhbeigag", "dhb",
				"cbgahbcjjcb", "jfbgegddgbfij", "bjhcaabhgcfcieai", "dfbedgacb", "bh", "hbgjhchebdigfef",
				"becbjjgbdgfg", "jigbiecdcegcgdha", "ddacfbgaibdag", "afid", "gijejaagbghjha", "becaigcjdbeiba", "gd",
				"cbfffhbacc", "jjbafcijeffacaej", "ihihgcgjgefiehgdijb", "afifbbhfbd", "dhigif", "chcfjjahbjjgjjheie",
				"ggfaaeeca", "afjiccee", "dddeigfhbgjiiffgf", "edbcfcbiibhcdbihahd", "jfhf", "cgeeefjhj", "ehaaahjbf",
				"dbdbfeabhhdfhedc", "jagiegfhgeicd", "cg", "fjhbaj", "djfejdacebedjjh", "ejhdbjaagcih", "hhifahefah",
				"decabhgbhf", "hjgfhdcfjghiehfbaccb", "hc", "cicefggjjhahhihh", "ebghgcehfdbgjef", "ihjfejiaidccj",
				"feebgfadjjih", "efdjbhbcdgfabia", "ebjdhij", "ccbjjbfgjifgibibhdi", "ddhgfihdifiegfdcbg", "jjhccchci",
				"bjhffdchjgfdejbjcc", "ghfhfadhadggbf", "degiigae", "ffefbjgfacjghchab", "affcadjjedffagcija",
				"hfaahajcijjigihjdbh", "eccahdhacfaaechc", "gaidhegbhdbg", "gdacg", "ajiafgjbi", "dcecgfgjh", "e",
				"cj", "iijjbfbciidi", "hhabcihigiccc", "hdje", "ghgiagda", "gcgii", "jgccffabdd", "eafd",
				"jgajgdghgjihfj", "hf", "jfhhagebiaage", "jcbgf", "cehifbja", "egidejh", "jd", "hhfgdcedjbafijia",
				"jejiajdffhdg", "ebdificebhah", "djddifjeb", "ibgfadfebjefjehed", "fcbad", "gfajh", "eabhddjadabaadc",
				"jfjdaibedicjfd", "a", "ahfiihcjceefjghjhi", "hdbcfidadjaggacigg", "bbfjhiegacbicihgbd",
				"beddihjhhjhi", "ahgideccga", "eadhajdegaig", "bccbgahhh", "ihfieebjejfhfh", "jddigigfhfegf",
				"acdihgjab", "hgcbfheehjafij", "hagfebifdcah", "ecfbiefefcgha", "giifif", "cfiadgbb", "faiecgcbaidi",
				"ffhcfc", "dgcbabfchj", "gchhhdhjjjjgfbeeaig", "jiebceebjeeiadcjehia", "ajbbhbighd", "hgiidjeagfgeejb",
				"gdehaffbfjc", "dhfibjfdfedbe", "hbeeedddgaaa", "bj", "fgdhidihjfbedbbhb", "dcigfcd",
				"jjgccccjfhjgagjbccbd", "djggj", "fdfbcaj", "hhh", "ebgddabghbje", "ijaeaihjbjgeb", "bcgf", "geabfbf",
				"ajdf", "behefaeeb", "icjecdbeejbg", "dcfhcchjabbbe", "ficggejecefjahagfc", "cbjbaaig",
				"cgghddihbibdahajjjj", "febcdicdjhigigjf", "jccfhaafj", "hgagaghagejgdbhiaa", "gdibfadcfjdchdcda",
				"faice", "jddahggg", "ig", "ajihabc", "ifc", "ddbdie", "hgf", "iicihahjicfbce", "egfjiifaigfhafdcdi",
				"gahbbfgebhajgajgf", "gibegcbhhjhcgeg", "gahahjjjid", "beeghbgiaiffcbedhi", "hb", "dgfdhbajiej",
				"ehjieabbfgjfabegijii", "chdafjb", "giejchjbifieeeigccah", "dadgcgjddbc", "cdiiea", "icdjffie",
				"iehihifddj", "jfcgfbjghbgfd", "edebbjiieahada", "badbhciaf", "icdffehcddgacgjcfji",
				"fgiheieeeibdjhhjae", "accebdijaedhhajaj", "acdgcbaehgaiedfcddf", "jiagjghcaihbf", "ga", "ggghd", "gb",
				"ehcjcd", "aac", "cdfghgfagbcjjc", "cddadcdidegifbi", "ddhhch", "fe", "eaageabiccfcdd", "fbbbjfjffj",
				"icjfacdcbdajecda", "aegdcbbicebaffaifg", "hedichggfajdbagh", "fggjjg", "bdbigbjbjadiabjbhch",
				"cdddaajifjjjiigj", "bhb", "faa", "bdfgebjf", "hicgahicd", "hcfghggjcibb", "ieddefeccfeccajhcah",
				"ghc", "jdgcbjaeeijjgciae", "bdeaif", "ehfdc", "jjjddhjd", "jibaejfc", "gddibbagdjbefaga", "fhca",
				"iaggggg", "bgbhgei", "gigfa", "fbibghagehecbedidbf", "igbfedebhcjbbcegaa", "cdceiffdjech",
				"fbdjdhhfgaija", "jgjccccchjabdgejfcj", "aca", "jghb", "ffeejefecheefdjh", "aediabejhghedgdah",
				"edfcbijbihjafedcc", "jbeg", "gfdeccbdgdgidabe", "figbaajccj", "dh", "eeafbfcccbjidci", "adfgdc",
				"becaafdhg", "cjfhajagc", "fhfifchf", "djdihjjdiibhaegfehc", "cgecbjhdjh", "acbfbccbiehjhjahjbic",
				"hhgbjdcidhdhdcijfdg", "jdcjaichdbiaefe", "bbdgfafiehc", "acdaajjfjcaeahcddage", "edbbehfdiddc",
				"ghabih", "ba", "dhjhdbieifabebajf", "cccdhicdbdf", "jfgdddh", "chhjg", "fgheacjabhiiihefbji",
				"jhcfbgbbgfe", "jgffhddba", "jibffbeijfcif", "dcghgfddfhj", "gaggjcdcaaf", "igjiaajgcjhbeeebdf",
				"gejibddcbj", "jcaaebfebjh", "jeedhcejgbegide", "jebfehdfdibg", "hdefhaia", "eb", "fjchhceceijfi",
				"egabjjcdbegfeabc", "gbiagfgfg", "gfajge", "iii", "dccjjeajd", "aihegdchjef", "gdaiegffaih",
				"haacjdcfheheeejefg", "bcde", "agcbagagadfjfdghdbb", "ejjiageabfh", "gichcecbfd", "iacajf",
				"fdfeaajhccbhb", "aecc", "da", "ecgcbdggffjg", "biebjjhfidb", "dadfcigjif", "badafaheg",
				"gddadiifadaa", "echjgchihgadb", "bhgaghbihef", "cjihigiiibdc", "bdheddceciaib", "ggegccjahfbib",
				"jfabidhcjefcfd", "iiiadhfhaig", "geedcbchc", "bafhbicaeidjg", "hfgiefdcgjjieejii",
				"hgiiigfcididicgaijde", "ihdbeahaehgd", "difgjfagjfidcdbggce", "ajdfddjbbdjjb", "iccabdaahhgcdejf",
				"gichhgejcgddcgbij", "jjea", "gcigbjhbaadjhi", "jjeeefibachiddid", "hjbehbeic", "adibfgfdgfgghgbggaa",
				"biggeedhffd", "hffdaaeidhfjgj", "ige", "ichijijc", "bhjh", "bifeidf", "hcgd", "jfbdabjbcadjgahgjd",
				"fhghdhfahibcbieiab", "gcjijfbiigiegb", "ibgabbhbijadhgib", "djadidiihhdfhiabb", "badefeccfjgca",
				"edehccejiajcb", "adjf", "afcefdjajhjhddffbjb", "biejjg", "ffjfhieaebhbiag", "gaegidbb", "jaahhjfca",
				"egg", "jeeaaffch", "bjaaafccjiii", "gcghehg", "egdibghgbhicdfdcicif", "jidaafdbhggfea",
				"daceegcdfbbbehejdgej", "jdbjcaad", "aihf", "fhgahbafcd", "bgcdcdejeiefdggfhha", "ccafhij",
				"hdahgjieaacabfa", "hgjeajaacfce", "jhejhibcbdacgjbjhbe", "hajgigd", "aaid", "fbjhbd",
				"eaddhgedigbffgbhcc", "diiiabffdifheaaahe", "cifigegjbibihd", "ahhiffjfff", "eebhji",
				"cidjigijdaghhcjic" };

		Solution solution = new Solution();
		List<List<Integer>> result = solution.palindromePairs(words);
		Arrays.sort(expected, this.comparator);
		assertTrue(Arrays.deepEquals(expected, convert(result)));
	}

	private Integer[][] convert(List<List<Integer>> ll)
	{
		Integer[][] a = new Integer[ll.size()][];

		int index = 0;

		for (List<Integer> l : ll)
		{
			a[index++] = l.toArray(new Integer[l.size()]);
		}

		Arrays.sort(a, this.comparator);

		return a;
	}
}
