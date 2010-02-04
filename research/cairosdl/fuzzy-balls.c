<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>
<head>
<title>~joonas/cairosdl - Unnamed repository; edit this file to name it for gitweb.</title>
<meta name='generator' content='cgit v0.8.3-6-g21f6'/>
<meta name='robots' content='index, nofollow'/>
<link rel='stylesheet' type='text/css' href='http://cgit.freedesktop.org/cgit.css'/>
<link rel='alternate' title='Atom feed' href='http://cgit.freedesktop.org/~joonas/cairosdl/atom/fuzzy-balls.c?h=demos' type='application/atom+xml'/>
</head>
<body>
<div id='cgit'><table id='header'>
<tr>
<td class='logo' rowspan='2'><a href='/'><img src='http://cgit.freedesktop.org/logo.png' alt='cgit logo'/></a></td>
<td class='main'><a href='/'>index</a> : <a title='~joonas/cairosdl' href='/~joonas/cairosdl/'>~joonas/cairosdl</a></td><td class='form'><form method='get' action=''>
<select name='h' onchange='this.form.submit();'>
<option value='demos' selected='selected'>demos</option>
<option value='master'>master</option>
</select> <input type='submit' name='' value='switch'/></form></td></tr>
<tr><td class='sub'>Unnamed repository; edit this file to name it for gitweb.</td><td class='sub right'>joonas</td></tr></table>
<table class='tabs'><tr><td>
<a href='/~joonas/cairosdl/?h=demos'>summary</a><a href='/~joonas/cairosdl/refs/?h=demos'>refs</a><a href='/~joonas/cairosdl/log/?h=demos'>log</a><a class='active' href='/~joonas/cairosdl/tree/?h=demos'>tree</a><a href='/~joonas/cairosdl/commit/?h=demos'>commit</a><a href='/~joonas/cairosdl/diff/?h=demos'>diff</a></td><td class='form'><form class='right' method='get' action='/~joonas/cairosdl/log/fuzzy-balls.c'>
<input type='hidden' name='h' value='demos'/><select name='qt'>
<option value='grep'>log msg</option>
<option value='author'>author</option>
<option value='committer'>committer</option>
</select>
<input class='txt' type='text' size='10' name='q' value=''/>
<input type='submit' value='search'/>
</form>
</td></tr></table>
<div class='content'>path: <a href='/~joonas/cairosdl/tree/?h=demos'>root</a>/<a href='/~joonas/cairosdl/tree/fuzzy-balls.c?h=demos'>fuzzy-balls.c</a> (<a href='/~joonas/cairosdl/plain/fuzzy-balls.c?h=demos'>plain</a>)<br/>blob: 5dc070545979811d0a59e1952002016167631933
<table summary='blob content' class='blob'>
<tr><td class='linenumbers'><pre><a class='no' id='n1' name='n1' href='#n1'>1</a>
<a class='no' id='n2' name='n2' href='#n2'>2</a>
<a class='no' id='n3' name='n3' href='#n3'>3</a>
<a class='no' id='n4' name='n4' href='#n4'>4</a>
<a class='no' id='n5' name='n5' href='#n5'>5</a>
<a class='no' id='n6' name='n6' href='#n6'>6</a>
<a class='no' id='n7' name='n7' href='#n7'>7</a>
<a class='no' id='n8' name='n8' href='#n8'>8</a>
<a class='no' id='n9' name='n9' href='#n9'>9</a>
<a class='no' id='n10' name='n10' href='#n10'>10</a>
<a class='no' id='n11' name='n11' href='#n11'>11</a>
<a class='no' id='n12' name='n12' href='#n12'>12</a>
<a class='no' id='n13' name='n13' href='#n13'>13</a>
<a class='no' id='n14' name='n14' href='#n14'>14</a>
<a class='no' id='n15' name='n15' href='#n15'>15</a>
<a class='no' id='n16' name='n16' href='#n16'>16</a>
<a class='no' id='n17' name='n17' href='#n17'>17</a>
<a class='no' id='n18' name='n18' href='#n18'>18</a>
<a class='no' id='n19' name='n19' href='#n19'>19</a>
<a class='no' id='n20' name='n20' href='#n20'>20</a>
<a class='no' id='n21' name='n21' href='#n21'>21</a>
<a class='no' id='n22' name='n22' href='#n22'>22</a>
<a class='no' id='n23' name='n23' href='#n23'>23</a>
<a class='no' id='n24' name='n24' href='#n24'>24</a>
<a class='no' id='n25' name='n25' href='#n25'>25</a>
<a class='no' id='n26' name='n26' href='#n26'>26</a>
<a class='no' id='n27' name='n27' href='#n27'>27</a>
<a class='no' id='n28' name='n28' href='#n28'>28</a>
<a class='no' id='n29' name='n29' href='#n29'>29</a>
<a class='no' id='n30' name='n30' href='#n30'>30</a>
<a class='no' id='n31' name='n31' href='#n31'>31</a>
<a class='no' id='n32' name='n32' href='#n32'>32</a>
<a class='no' id='n33' name='n33' href='#n33'>33</a>
<a class='no' id='n34' name='n34' href='#n34'>34</a>
<a class='no' id='n35' name='n35' href='#n35'>35</a>
<a class='no' id='n36' name='n36' href='#n36'>36</a>
<a class='no' id='n37' name='n37' href='#n37'>37</a>
<a class='no' id='n38' name='n38' href='#n38'>38</a>
<a class='no' id='n39' name='n39' href='#n39'>39</a>
<a class='no' id='n40' name='n40' href='#n40'>40</a>
<a class='no' id='n41' name='n41' href='#n41'>41</a>
<a class='no' id='n42' name='n42' href='#n42'>42</a>
<a class='no' id='n43' name='n43' href='#n43'>43</a>
<a class='no' id='n44' name='n44' href='#n44'>44</a>
<a class='no' id='n45' name='n45' href='#n45'>45</a>
<a class='no' id='n46' name='n46' href='#n46'>46</a>
<a class='no' id='n47' name='n47' href='#n47'>47</a>
<a class='no' id='n48' name='n48' href='#n48'>48</a>
<a class='no' id='n49' name='n49' href='#n49'>49</a>
<a class='no' id='n50' name='n50' href='#n50'>50</a>
<a class='no' id='n51' name='n51' href='#n51'>51</a>
<a class='no' id='n52' name='n52' href='#n52'>52</a>
<a class='no' id='n53' name='n53' href='#n53'>53</a>
<a class='no' id='n54' name='n54' href='#n54'>54</a>
<a class='no' id='n55' name='n55' href='#n55'>55</a>
<a class='no' id='n56' name='n56' href='#n56'>56</a>
<a class='no' id='n57' name='n57' href='#n57'>57</a>
<a class='no' id='n58' name='n58' href='#n58'>58</a>
<a class='no' id='n59' name='n59' href='#n59'>59</a>
<a class='no' id='n60' name='n60' href='#n60'>60</a>
<a class='no' id='n61' name='n61' href='#n61'>61</a>
<a class='no' id='n62' name='n62' href='#n62'>62</a>
<a class='no' id='n63' name='n63' href='#n63'>63</a>
<a class='no' id='n64' name='n64' href='#n64'>64</a>
<a class='no' id='n65' name='n65' href='#n65'>65</a>
<a class='no' id='n66' name='n66' href='#n66'>66</a>
<a class='no' id='n67' name='n67' href='#n67'>67</a>
<a class='no' id='n68' name='n68' href='#n68'>68</a>
<a class='no' id='n69' name='n69' href='#n69'>69</a>
<a class='no' id='n70' name='n70' href='#n70'>70</a>
<a class='no' id='n71' name='n71' href='#n71'>71</a>
<a class='no' id='n72' name='n72' href='#n72'>72</a>
<a class='no' id='n73' name='n73' href='#n73'>73</a>
<a class='no' id='n74' name='n74' href='#n74'>74</a>
<a class='no' id='n75' name='n75' href='#n75'>75</a>
<a class='no' id='n76' name='n76' href='#n76'>76</a>
<a class='no' id='n77' name='n77' href='#n77'>77</a>
<a class='no' id='n78' name='n78' href='#n78'>78</a>
<a class='no' id='n79' name='n79' href='#n79'>79</a>
<a class='no' id='n80' name='n80' href='#n80'>80</a>
<a class='no' id='n81' name='n81' href='#n81'>81</a>
<a class='no' id='n82' name='n82' href='#n82'>82</a>
<a class='no' id='n83' name='n83' href='#n83'>83</a>
<a class='no' id='n84' name='n84' href='#n84'>84</a>
<a class='no' id='n85' name='n85' href='#n85'>85</a>
<a class='no' id='n86' name='n86' href='#n86'>86</a>
<a class='no' id='n87' name='n87' href='#n87'>87</a>
<a class='no' id='n88' name='n88' href='#n88'>88</a>
<a class='no' id='n89' name='n89' href='#n89'>89</a>
<a class='no' id='n90' name='n90' href='#n90'>90</a>
<a class='no' id='n91' name='n91' href='#n91'>91</a>
<a class='no' id='n92' name='n92' href='#n92'>92</a>
<a class='no' id='n93' name='n93' href='#n93'>93</a>
<a class='no' id='n94' name='n94' href='#n94'>94</a>
<a class='no' id='n95' name='n95' href='#n95'>95</a>
<a class='no' id='n96' name='n96' href='#n96'>96</a>
<a class='no' id='n97' name='n97' href='#n97'>97</a>
<a class='no' id='n98' name='n98' href='#n98'>98</a>
<a class='no' id='n99' name='n99' href='#n99'>99</a>
<a class='no' id='n100' name='n100' href='#n100'>100</a>
<a class='no' id='n101' name='n101' href='#n101'>101</a>
<a class='no' id='n102' name='n102' href='#n102'>102</a>
<a class='no' id='n103' name='n103' href='#n103'>103</a>
<a class='no' id='n104' name='n104' href='#n104'>104</a>
<a class='no' id='n105' name='n105' href='#n105'>105</a>
<a class='no' id='n106' name='n106' href='#n106'>106</a>
<a class='no' id='n107' name='n107' href='#n107'>107</a>
<a class='no' id='n108' name='n108' href='#n108'>108</a>
<a class='no' id='n109' name='n109' href='#n109'>109</a>
<a class='no' id='n110' name='n110' href='#n110'>110</a>
<a class='no' id='n111' name='n111' href='#n111'>111</a>
<a class='no' id='n112' name='n112' href='#n112'>112</a>
<a class='no' id='n113' name='n113' href='#n113'>113</a>
<a class='no' id='n114' name='n114' href='#n114'>114</a>
<a class='no' id='n115' name='n115' href='#n115'>115</a>
<a class='no' id='n116' name='n116' href='#n116'>116</a>
<a class='no' id='n117' name='n117' href='#n117'>117</a>
<a class='no' id='n118' name='n118' href='#n118'>118</a>
<a class='no' id='n119' name='n119' href='#n119'>119</a>
<a class='no' id='n120' name='n120' href='#n120'>120</a>
<a class='no' id='n121' name='n121' href='#n121'>121</a>
<a class='no' id='n122' name='n122' href='#n122'>122</a>
<a class='no' id='n123' name='n123' href='#n123'>123</a>
<a class='no' id='n124' name='n124' href='#n124'>124</a>
<a class='no' id='n125' name='n125' href='#n125'>125</a>
<a class='no' id='n126' name='n126' href='#n126'>126</a>
<a class='no' id='n127' name='n127' href='#n127'>127</a>
<a class='no' id='n128' name='n128' href='#n128'>128</a>
<a class='no' id='n129' name='n129' href='#n129'>129</a>
<a class='no' id='n130' name='n130' href='#n130'>130</a>
<a class='no' id='n131' name='n131' href='#n131'>131</a>
<a class='no' id='n132' name='n132' href='#n132'>132</a>
<a class='no' id='n133' name='n133' href='#n133'>133</a>
<a class='no' id='n134' name='n134' href='#n134'>134</a>
<a class='no' id='n135' name='n135' href='#n135'>135</a>
<a class='no' id='n136' name='n136' href='#n136'>136</a>
<a class='no' id='n137' name='n137' href='#n137'>137</a>
<a class='no' id='n138' name='n138' href='#n138'>138</a>
<a class='no' id='n139' name='n139' href='#n139'>139</a>
<a class='no' id='n140' name='n140' href='#n140'>140</a>
<a class='no' id='n141' name='n141' href='#n141'>141</a>
<a class='no' id='n142' name='n142' href='#n142'>142</a>
<a class='no' id='n143' name='n143' href='#n143'>143</a>
<a class='no' id='n144' name='n144' href='#n144'>144</a>
<a class='no' id='n145' name='n145' href='#n145'>145</a>
<a class='no' id='n146' name='n146' href='#n146'>146</a>
<a class='no' id='n147' name='n147' href='#n147'>147</a>
<a class='no' id='n148' name='n148' href='#n148'>148</a>
<a class='no' id='n149' name='n149' href='#n149'>149</a>
<a class='no' id='n150' name='n150' href='#n150'>150</a>
<a class='no' id='n151' name='n151' href='#n151'>151</a>
<a class='no' id='n152' name='n152' href='#n152'>152</a>
<a class='no' id='n153' name='n153' href='#n153'>153</a>
<a class='no' id='n154' name='n154' href='#n154'>154</a>
<a class='no' id='n155' name='n155' href='#n155'>155</a>
<a class='no' id='n156' name='n156' href='#n156'>156</a>
<a class='no' id='n157' name='n157' href='#n157'>157</a>
<a class='no' id='n158' name='n158' href='#n158'>158</a>
<a class='no' id='n159' name='n159' href='#n159'>159</a>
<a class='no' id='n160' name='n160' href='#n160'>160</a>
<a class='no' id='n161' name='n161' href='#n161'>161</a>
<a class='no' id='n162' name='n162' href='#n162'>162</a>
<a class='no' id='n163' name='n163' href='#n163'>163</a>
<a class='no' id='n164' name='n164' href='#n164'>164</a>
<a class='no' id='n165' name='n165' href='#n165'>165</a>
<a class='no' id='n166' name='n166' href='#n166'>166</a>
<a class='no' id='n167' name='n167' href='#n167'>167</a>
<a class='no' id='n168' name='n168' href='#n168'>168</a>
<a class='no' id='n169' name='n169' href='#n169'>169</a>
<a class='no' id='n170' name='n170' href='#n170'>170</a>
<a class='no' id='n171' name='n171' href='#n171'>171</a>
<a class='no' id='n172' name='n172' href='#n172'>172</a>
<a class='no' id='n173' name='n173' href='#n173'>173</a>
<a class='no' id='n174' name='n174' href='#n174'>174</a>
<a class='no' id='n175' name='n175' href='#n175'>175</a>
<a class='no' id='n176' name='n176' href='#n176'>176</a>
<a class='no' id='n177' name='n177' href='#n177'>177</a>
<a class='no' id='n178' name='n178' href='#n178'>178</a>
<a class='no' id='n179' name='n179' href='#n179'>179</a>
<a class='no' id='n180' name='n180' href='#n180'>180</a>
<a class='no' id='n181' name='n181' href='#n181'>181</a>
<a class='no' id='n182' name='n182' href='#n182'>182</a>
<a class='no' id='n183' name='n183' href='#n183'>183</a>
<a class='no' id='n184' name='n184' href='#n184'>184</a>
<a class='no' id='n185' name='n185' href='#n185'>185</a>
<a class='no' id='n186' name='n186' href='#n186'>186</a>
<a class='no' id='n187' name='n187' href='#n187'>187</a>
<a class='no' id='n188' name='n188' href='#n188'>188</a>
<a class='no' id='n189' name='n189' href='#n189'>189</a>
<a class='no' id='n190' name='n190' href='#n190'>190</a>
<a class='no' id='n191' name='n191' href='#n191'>191</a>
<a class='no' id='n192' name='n192' href='#n192'>192</a>
<a class='no' id='n193' name='n193' href='#n193'>193</a>
<a class='no' id='n194' name='n194' href='#n194'>194</a>
<a class='no' id='n195' name='n195' href='#n195'>195</a>
<a class='no' id='n196' name='n196' href='#n196'>196</a>
<a class='no' id='n197' name='n197' href='#n197'>197</a>
<a class='no' id='n198' name='n198' href='#n198'>198</a>
<a class='no' id='n199' name='n199' href='#n199'>199</a>
<a class='no' id='n200' name='n200' href='#n200'>200</a>
<a class='no' id='n201' name='n201' href='#n201'>201</a>
<a class='no' id='n202' name='n202' href='#n202'>202</a>
<a class='no' id='n203' name='n203' href='#n203'>203</a>
<a class='no' id='n204' name='n204' href='#n204'>204</a>
<a class='no' id='n205' name='n205' href='#n205'>205</a>
<a class='no' id='n206' name='n206' href='#n206'>206</a>
<a class='no' id='n207' name='n207' href='#n207'>207</a>
<a class='no' id='n208' name='n208' href='#n208'>208</a>
<a class='no' id='n209' name='n209' href='#n209'>209</a>
<a class='no' id='n210' name='n210' href='#n210'>210</a>
<a class='no' id='n211' name='n211' href='#n211'>211</a>
<a class='no' id='n212' name='n212' href='#n212'>212</a>
<a class='no' id='n213' name='n213' href='#n213'>213</a>
<a class='no' id='n214' name='n214' href='#n214'>214</a>
<a class='no' id='n215' name='n215' href='#n215'>215</a>
<a class='no' id='n216' name='n216' href='#n216'>216</a>
<a class='no' id='n217' name='n217' href='#n217'>217</a>
<a class='no' id='n218' name='n218' href='#n218'>218</a>
<a class='no' id='n219' name='n219' href='#n219'>219</a>
<a class='no' id='n220' name='n220' href='#n220'>220</a>
<a class='no' id='n221' name='n221' href='#n221'>221</a>
<a class='no' id='n222' name='n222' href='#n222'>222</a>
<a class='no' id='n223' name='n223' href='#n223'>223</a>
<a class='no' id='n224' name='n224' href='#n224'>224</a>
<a class='no' id='n225' name='n225' href='#n225'>225</a>
<a class='no' id='n226' name='n226' href='#n226'>226</a>
<a class='no' id='n227' name='n227' href='#n227'>227</a>
<a class='no' id='n228' name='n228' href='#n228'>228</a>
<a class='no' id='n229' name='n229' href='#n229'>229</a>
<a class='no' id='n230' name='n230' href='#n230'>230</a>
<a class='no' id='n231' name='n231' href='#n231'>231</a>
<a class='no' id='n232' name='n232' href='#n232'>232</a>
<a class='no' id='n233' name='n233' href='#n233'>233</a>
<a class='no' id='n234' name='n234' href='#n234'>234</a>
<a class='no' id='n235' name='n235' href='#n235'>235</a>
<a class='no' id='n236' name='n236' href='#n236'>236</a>
<a class='no' id='n237' name='n237' href='#n237'>237</a>
<a class='no' id='n238' name='n238' href='#n238'>238</a>
<a class='no' id='n239' name='n239' href='#n239'>239</a>
<a class='no' id='n240' name='n240' href='#n240'>240</a>
<a class='no' id='n241' name='n241' href='#n241'>241</a>
<a class='no' id='n242' name='n242' href='#n242'>242</a>
<a class='no' id='n243' name='n243' href='#n243'>243</a>
<a class='no' id='n244' name='n244' href='#n244'>244</a>
<a class='no' id='n245' name='n245' href='#n245'>245</a>
<a class='no' id='n246' name='n246' href='#n246'>246</a>
<a class='no' id='n247' name='n247' href='#n247'>247</a>
<a class='no' id='n248' name='n248' href='#n248'>248</a>
<a class='no' id='n249' name='n249' href='#n249'>249</a>
<a class='no' id='n250' name='n250' href='#n250'>250</a>
<a class='no' id='n251' name='n251' href='#n251'>251</a>
<a class='no' id='n252' name='n252' href='#n252'>252</a>
<a class='no' id='n253' name='n253' href='#n253'>253</a>
<a class='no' id='n254' name='n254' href='#n254'>254</a>
<a class='no' id='n255' name='n255' href='#n255'>255</a>
<a class='no' id='n256' name='n256' href='#n256'>256</a>
<a class='no' id='n257' name='n257' href='#n257'>257</a>
<a class='no' id='n258' name='n258' href='#n258'>258</a>
<a class='no' id='n259' name='n259' href='#n259'>259</a>
<a class='no' id='n260' name='n260' href='#n260'>260</a>
<a class='no' id='n261' name='n261' href='#n261'>261</a>
<a class='no' id='n262' name='n262' href='#n262'>262</a>
<a class='no' id='n263' name='n263' href='#n263'>263</a>
<a class='no' id='n264' name='n264' href='#n264'>264</a>
<a class='no' id='n265' name='n265' href='#n265'>265</a>
<a class='no' id='n266' name='n266' href='#n266'>266</a>
<a class='no' id='n267' name='n267' href='#n267'>267</a>
<a class='no' id='n268' name='n268' href='#n268'>268</a>
<a class='no' id='n269' name='n269' href='#n269'>269</a>
<a class='no' id='n270' name='n270' href='#n270'>270</a>
<a class='no' id='n271' name='n271' href='#n271'>271</a>
<a class='no' id='n272' name='n272' href='#n272'>272</a>
<a class='no' id='n273' name='n273' href='#n273'>273</a>
<a class='no' id='n274' name='n274' href='#n274'>274</a>
<a class='no' id='n275' name='n275' href='#n275'>275</a>
<a class='no' id='n276' name='n276' href='#n276'>276</a>
<a class='no' id='n277' name='n277' href='#n277'>277</a>
<a class='no' id='n278' name='n278' href='#n278'>278</a>
<a class='no' id='n279' name='n279' href='#n279'>279</a>
<a class='no' id='n280' name='n280' href='#n280'>280</a>
<a class='no' id='n281' name='n281' href='#n281'>281</a>
<a class='no' id='n282' name='n282' href='#n282'>282</a>
<a class='no' id='n283' name='n283' href='#n283'>283</a>
<a class='no' id='n284' name='n284' href='#n284'>284</a>
<a class='no' id='n285' name='n285' href='#n285'>285</a>
<a class='no' id='n286' name='n286' href='#n286'>286</a>
<a class='no' id='n287' name='n287' href='#n287'>287</a>
<a class='no' id='n288' name='n288' href='#n288'>288</a>
<a class='no' id='n289' name='n289' href='#n289'>289</a>
<a class='no' id='n290' name='n290' href='#n290'>290</a>
<a class='no' id='n291' name='n291' href='#n291'>291</a>
<a class='no' id='n292' name='n292' href='#n292'>292</a>
<a class='no' id='n293' name='n293' href='#n293'>293</a>
<a class='no' id='n294' name='n294' href='#n294'>294</a>
<a class='no' id='n295' name='n295' href='#n295'>295</a>
<a class='no' id='n296' name='n296' href='#n296'>296</a>
<a class='no' id='n297' name='n297' href='#n297'>297</a>
<a class='no' id='n298' name='n298' href='#n298'>298</a>
<a class='no' id='n299' name='n299' href='#n299'>299</a>
<a class='no' id='n300' name='n300' href='#n300'>300</a>
<a class='no' id='n301' name='n301' href='#n301'>301</a>
<a class='no' id='n302' name='n302' href='#n302'>302</a>
<a class='no' id='n303' name='n303' href='#n303'>303</a>
<a class='no' id='n304' name='n304' href='#n304'>304</a>
<a class='no' id='n305' name='n305' href='#n305'>305</a>
<a class='no' id='n306' name='n306' href='#n306'>306</a>
<a class='no' id='n307' name='n307' href='#n307'>307</a>
<a class='no' id='n308' name='n308' href='#n308'>308</a>
<a class='no' id='n309' name='n309' href='#n309'>309</a>
<a class='no' id='n310' name='n310' href='#n310'>310</a>
<a class='no' id='n311' name='n311' href='#n311'>311</a>
<a class='no' id='n312' name='n312' href='#n312'>312</a>
<a class='no' id='n313' name='n313' href='#n313'>313</a>
<a class='no' id='n314' name='n314' href='#n314'>314</a>
<a class='no' id='n315' name='n315' href='#n315'>315</a>
<a class='no' id='n316' name='n316' href='#n316'>316</a>
<a class='no' id='n317' name='n317' href='#n317'>317</a>
<a class='no' id='n318' name='n318' href='#n318'>318</a>
<a class='no' id='n319' name='n319' href='#n319'>319</a>
<a class='no' id='n320' name='n320' href='#n320'>320</a>
<a class='no' id='n321' name='n321' href='#n321'>321</a>
<a class='no' id='n322' name='n322' href='#n322'>322</a>
<a class='no' id='n323' name='n323' href='#n323'>323</a>
<a class='no' id='n324' name='n324' href='#n324'>324</a>
<a class='no' id='n325' name='n325' href='#n325'>325</a>
<a class='no' id='n326' name='n326' href='#n326'>326</a>
<a class='no' id='n327' name='n327' href='#n327'>327</a>
<a class='no' id='n328' name='n328' href='#n328'>328</a>
<a class='no' id='n329' name='n329' href='#n329'>329</a>
<a class='no' id='n330' name='n330' href='#n330'>330</a>
<a class='no' id='n331' name='n331' href='#n331'>331</a>
<a class='no' id='n332' name='n332' href='#n332'>332</a>
<a class='no' id='n333' name='n333' href='#n333'>333</a>
<a class='no' id='n334' name='n334' href='#n334'>334</a>
<a class='no' id='n335' name='n335' href='#n335'>335</a>
<a class='no' id='n336' name='n336' href='#n336'>336</a>
<a class='no' id='n337' name='n337' href='#n337'>337</a>
<a class='no' id='n338' name='n338' href='#n338'>338</a>
<a class='no' id='n339' name='n339' href='#n339'>339</a>
<a class='no' id='n340' name='n340' href='#n340'>340</a>
<a class='no' id='n341' name='n341' href='#n341'>341</a>
<a class='no' id='n342' name='n342' href='#n342'>342</a>
<a class='no' id='n343' name='n343' href='#n343'>343</a>
<a class='no' id='n344' name='n344' href='#n344'>344</a>
<a class='no' id='n345' name='n345' href='#n345'>345</a>
<a class='no' id='n346' name='n346' href='#n346'>346</a>
<a class='no' id='n347' name='n347' href='#n347'>347</a>
<a class='no' id='n348' name='n348' href='#n348'>348</a>
<a class='no' id='n349' name='n349' href='#n349'>349</a>
<a class='no' id='n350' name='n350' href='#n350'>350</a>
<a class='no' id='n351' name='n351' href='#n351'>351</a>
<a class='no' id='n352' name='n352' href='#n352'>352</a>
<a class='no' id='n353' name='n353' href='#n353'>353</a>
<a class='no' id='n354' name='n354' href='#n354'>354</a>
<a class='no' id='n355' name='n355' href='#n355'>355</a>
<a class='no' id='n356' name='n356' href='#n356'>356</a>
<a class='no' id='n357' name='n357' href='#n357'>357</a>
<a class='no' id='n358' name='n358' href='#n358'>358</a>
<a class='no' id='n359' name='n359' href='#n359'>359</a>
<a class='no' id='n360' name='n360' href='#n360'>360</a>
<a class='no' id='n361' name='n361' href='#n361'>361</a>
<a class='no' id='n362' name='n362' href='#n362'>362</a>
<a class='no' id='n363' name='n363' href='#n363'>363</a>
<a class='no' id='n364' name='n364' href='#n364'>364</a>
<a class='no' id='n365' name='n365' href='#n365'>365</a>
<a class='no' id='n366' name='n366' href='#n366'>366</a>
<a class='no' id='n367' name='n367' href='#n367'>367</a>
<a class='no' id='n368' name='n368' href='#n368'>368</a>
<a class='no' id='n369' name='n369' href='#n369'>369</a>
<a class='no' id='n370' name='n370' href='#n370'>370</a>
<a class='no' id='n371' name='n371' href='#n371'>371</a>
<a class='no' id='n372' name='n372' href='#n372'>372</a>
<a class='no' id='n373' name='n373' href='#n373'>373</a>
<a class='no' id='n374' name='n374' href='#n374'>374</a>
<a class='no' id='n375' name='n375' href='#n375'>375</a>
<a class='no' id='n376' name='n376' href='#n376'>376</a>
<a class='no' id='n377' name='n377' href='#n377'>377</a>
<a class='no' id='n378' name='n378' href='#n378'>378</a>
<a class='no' id='n379' name='n379' href='#n379'>379</a>
<a class='no' id='n380' name='n380' href='#n380'>380</a>
<a class='no' id='n381' name='n381' href='#n381'>381</a>
<a class='no' id='n382' name='n382' href='#n382'>382</a>
<a class='no' id='n383' name='n383' href='#n383'>383</a>
<a class='no' id='n384' name='n384' href='#n384'>384</a>
<a class='no' id='n385' name='n385' href='#n385'>385</a>
<a class='no' id='n386' name='n386' href='#n386'>386</a>
<a class='no' id='n387' name='n387' href='#n387'>387</a>
<a class='no' id='n388' name='n388' href='#n388'>388</a>
<a class='no' id='n389' name='n389' href='#n389'>389</a>
<a class='no' id='n390' name='n390' href='#n390'>390</a>
<a class='no' id='n391' name='n391' href='#n391'>391</a>
<a class='no' id='n392' name='n392' href='#n392'>392</a>
<a class='no' id='n393' name='n393' href='#n393'>393</a>
<a class='no' id='n394' name='n394' href='#n394'>394</a>
<a class='no' id='n395' name='n395' href='#n395'>395</a>
<a class='no' id='n396' name='n396' href='#n396'>396</a>
<a class='no' id='n397' name='n397' href='#n397'>397</a>
<a class='no' id='n398' name='n398' href='#n398'>398</a>
<a class='no' id='n399' name='n399' href='#n399'>399</a>
<a class='no' id='n400' name='n400' href='#n400'>400</a>
<a class='no' id='n401' name='n401' href='#n401'>401</a>
<a class='no' id='n402' name='n402' href='#n402'>402</a>
<a class='no' id='n403' name='n403' href='#n403'>403</a>
<a class='no' id='n404' name='n404' href='#n404'>404</a>
<a class='no' id='n405' name='n405' href='#n405'>405</a>
<a class='no' id='n406' name='n406' href='#n406'>406</a>
<a class='no' id='n407' name='n407' href='#n407'>407</a>
<a class='no' id='n408' name='n408' href='#n408'>408</a>
<a class='no' id='n409' name='n409' href='#n409'>409</a>
<a class='no' id='n410' name='n410' href='#n410'>410</a>
<a class='no' id='n411' name='n411' href='#n411'>411</a>
<a class='no' id='n412' name='n412' href='#n412'>412</a>
<a class='no' id='n413' name='n413' href='#n413'>413</a>
<a class='no' id='n414' name='n414' href='#n414'>414</a>
<a class='no' id='n415' name='n415' href='#n415'>415</a>
<a class='no' id='n416' name='n416' href='#n416'>416</a>
<a class='no' id='n417' name='n417' href='#n417'>417</a>
<a class='no' id='n418' name='n418' href='#n418'>418</a>
<a class='no' id='n419' name='n419' href='#n419'>419</a>
<a class='no' id='n420' name='n420' href='#n420'>420</a>
<a class='no' id='n421' name='n421' href='#n421'>421</a>
<a class='no' id='n422' name='n422' href='#n422'>422</a>
<a class='no' id='n423' name='n423' href='#n423'>423</a>
<a class='no' id='n424' name='n424' href='#n424'>424</a>
<a class='no' id='n425' name='n425' href='#n425'>425</a>
<a class='no' id='n426' name='n426' href='#n426'>426</a>
<a class='no' id='n427' name='n427' href='#n427'>427</a>
<a class='no' id='n428' name='n428' href='#n428'>428</a>
<a class='no' id='n429' name='n429' href='#n429'>429</a>
<a class='no' id='n430' name='n430' href='#n430'>430</a>
<a class='no' id='n431' name='n431' href='#n431'>431</a>
<a class='no' id='n432' name='n432' href='#n432'>432</a>
<a class='no' id='n433' name='n433' href='#n433'>433</a>
<a class='no' id='n434' name='n434' href='#n434'>434</a>
<a class='no' id='n435' name='n435' href='#n435'>435</a>
<a class='no' id='n436' name='n436' href='#n436'>436</a>
<a class='no' id='n437' name='n437' href='#n437'>437</a>
<a class='no' id='n438' name='n438' href='#n438'>438</a>
<a class='no' id='n439' name='n439' href='#n439'>439</a>
<a class='no' id='n440' name='n440' href='#n440'>440</a>
<a class='no' id='n441' name='n441' href='#n441'>441</a>
<a class='no' id='n442' name='n442' href='#n442'>442</a>
<a class='no' id='n443' name='n443' href='#n443'>443</a>
<a class='no' id='n444' name='n444' href='#n444'>444</a>
<a class='no' id='n445' name='n445' href='#n445'>445</a>
<a class='no' id='n446' name='n446' href='#n446'>446</a>
<a class='no' id='n447' name='n447' href='#n447'>447</a>
<a class='no' id='n448' name='n448' href='#n448'>448</a>
<a class='no' id='n449' name='n449' href='#n449'>449</a>
<a class='no' id='n450' name='n450' href='#n450'>450</a>
<a class='no' id='n451' name='n451' href='#n451'>451</a>
<a class='no' id='n452' name='n452' href='#n452'>452</a>
<a class='no' id='n453' name='n453' href='#n453'>453</a>
<a class='no' id='n454' name='n454' href='#n454'>454</a>
<a class='no' id='n455' name='n455' href='#n455'>455</a>
<a class='no' id='n456' name='n456' href='#n456'>456</a>
<a class='no' id='n457' name='n457' href='#n457'>457</a>
<a class='no' id='n458' name='n458' href='#n458'>458</a>
<a class='no' id='n459' name='n459' href='#n459'>459</a>
</pre></td>
<td class='lines'><pre><code>#include &lt;assert.h&gt;
#include &lt;math.h&gt;
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include "cairosdl.h"

#define dprintf(args)

#define BLIT_BOBS_USING_CAIRO 1

struct vector {
    double x, y;
};

#define MAX_BOBS 20

struct bob {
    struct vector pos;
    struct vector vel;
    struct vector accel;
    double mass;
    double radius;
    double focus;
    cairo_surface_t *surface;
};

static void
init_bobs (struct bob *bobs, size_t num_bobs)
{
    size_t i;
    double fill_ratio = 0.95;
    double n = sqrt(num_bobs);

    for (i=0; i&lt;num_bobs; i++) {
        struct bob *bob = bobs + i;
        double theta = 1.0 - (i+0.5) / MAX_BOBS;
        double r = fill_ratio*(0.5 + theta*0.0)/n;
        r = r &lt; 0.2 ? r : 0.2;
        bob-&gt;pos.x = rand () * 1.0 / RAND_MAX;
        bob-&gt;pos.y = rand () * 1.0 / RAND_MAX;
        bob-&gt;vel.x = bob-&gt;vel.y = 0;
        bob-&gt;accel.x = bob-&gt;accel.y = 0;
        bob-&gt;mass = (1+theta)*(1+theta);
        bob-&gt;mass = 1.0;      /* equal mass bobs have a smoother ride */
        bob-&gt;mass /= num_bobs;
        bob-&gt;radius = r;
        bob-&gt;focus = 1.0;
        bob-&gt;surface = NULL;
    }
}

static void
alloc_bobs (struct bob *bobs, size_t num_bobs)
{
    size_t i;
    SDL_Surface *screen = SDL_GetVideoSurface ();

    for (i=0; i&lt;num_bobs; i++) {
        struct bob *bob = bobs + i;
        int width = screen-&gt;w * 2*bob-&gt;radius + 1;
        int height = screen-&gt;h * 2*bob-&gt;radius + 1;

        if (bob-&gt;surface) {
            cairo_surface_destroy (bob-&gt;surface);
            bob-&gt;surface = NULL;
        }

        if (BLIT_BOBS_USING_CAIRO) {
            bob-&gt;surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                                       width, height);
        }
        else {
            SDL_Surface *sdl_surface = SDL_CreateRGBSurface (
                SDL_SWSURFACE | SDL_SRCALPHA,
                width, height, 32,
                CAIROSDL_RMASK,
                CAIROSDL_GMASK,
                CAIROSDL_BMASK,
                CAIROSDL_AMASK);
            if (sdl_surface == NULL) {
                fprintf (stderr, "Failed allocating bob sdl surfaces: %s\n",
                         SDL_GetError ());
                exit (1);
            }
            assert (!SDL_MUSTLOCK (sdl_surface));
            bob-&gt;surface = cairosdl_surface_create (sdl_surface);
            SDL_FreeSurface (sdl_surface);
        }

        if (cairo_surface_status (bob-&gt;surface) != CAIRO_STATUS_SUCCESS) {
            cairo_status_t status = cairo_surface_status (bob-&gt;surface);
            fprintf (stderr, "Failed making a cairo surface for a bob: %s\n",
                     cairo_status_to_string (status));
            exit (1);
        }

    }
}

static void
render_bob (struct bob *bob, int i)
{
    int width = cairo_image_surface_get_width (bob-&gt;surface);
    int height = cairo_image_surface_get_height (bob-&gt;surface);
    cairo_t *cr = cairo_create (bob-&gt;surface);
    double theta = (i+0.5) / MAX_BOBS;
    double dx = bob-&gt;pos.x - 0.5;
    double dy = bob-&gt;pos.y - 0.5;

    cairo_scale (cr, 0.5*width, 0.5*height);
    cairo_translate (cr, 1.0, 1.0);

    cairo_set_tolerance (cr, 0.5);

    cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint (cr);

    cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

    cairo_set_source_rgba (cr,
                           1-fabs(dx),
                           1-fabs(dy),
                           theta,
                           (1-2*fabs(dx))*(1-2*fabs(dy)));
    if (1) {
        cairo_pattern_t *pat;
        pat = cairo_pattern_create_radial (
            -dx, -dy, 0.0,
            0, 0, 1.0);
        cairo_pattern_add_color_stop_rgba (pat, 0.0,
                                           fabs(dy),
                                           0,
                                           fabs(dx),
                                           0);

        cairo_pattern_add_color_stop_rgba (pat, bob-&gt;focus,
                                           fabs(dx+dy),
                                           i&amp;1 ? 1 : 1,
                                           i&amp;1 ? fabs(dx) : 1-fabs(dx),
                                           0.6);

        cairo_pattern_add_color_stop_rgba (pat, 1.0,
                                           1 - fabs(dy),
                                           1 - fabs(dx),
                                           theta,
                                           0.0);

        cairo_set_source (cr, pat);
        cairo_pattern_destroy (pat);
    }

    cairo_arc (cr, 0,0, 1.0, 0, 6.29);
    cairo_close_path (cr);
    cairo_fill (cr);

    cairosdl_destroy (cr);
}

static void
render_bobs (struct bob *bobs, size_t num_bobs)
{
    size_t i;
    for (i=0; i&lt;num_bobs; i++) {
        render_bob (bobs+i, i);
    }
}

static void
blit_bobs_using_sdl (struct bob *bobs, size_t num_bobs)
{
    size_t i;
    SDL_Surface *screen = SDL_GetVideoSurface ();

    for (i=0; i&lt;num_bobs; i++) {
        struct bob *bob = bobs + i;
        SDL_Surface *sdl_surface = cairosdl_surface_get_target (bob-&gt;surface);
        SDL_Rect src_rect[1];
        SDL_Rect dst_rect[1];

        src_rect-&gt;x = 0;
        src_rect-&gt;y = 0;
        src_rect-&gt;w = sdl_surface-&gt;w;
        src_rect-&gt;h = sdl_surface-&gt;h;

        dst_rect-&gt;x = (bob-&gt;pos.x - bob-&gt;radius) * screen-&gt;w;
        dst_rect-&gt;y = (bob-&gt;pos.y - bob-&gt;radius) * screen-&gt;h;
        dst_rect-&gt;w = sdl_surface-&gt;w;
        dst_rect-&gt;h = sdl_surface-&gt;h;

        SDL_BlitSurface (sdl_surface, src_rect, screen, dst_rect);
    }
}

static void
blit_bobs_using_cairo (struct bob *bobs, size_t num_bobs)
{
    size_t i;
    SDL_Surface *screen = SDL_GetVideoSurface ();
    cairo_t *cr;

    while (SDL_LockSurface (screen) != 0) {
        SDL_Delay (1);
    }

    cr = cairosdl_create (screen);

    for (i=0; i&lt;num_bobs; i++) {
        struct bob *bob = bobs + i;
        int x = (int)((bob-&gt;pos.x - bob-&gt;radius) * screen-&gt;w);
        int y = (int)((bob-&gt;pos.y - bob-&gt;radius) * screen-&gt;h);
        int width = cairo_image_surface_get_width (bob-&gt;surface);
        int height = cairo_image_surface_get_height (bob-&gt;surface);

        cairo_set_source_surface (cr, bob-&gt;surface, x,y);
        cairo_rectangle (cr,
                         x, y,
                         width, height);
        cairo_fill (cr);
    }

    cairo_destroy (cr);

    SDL_UnlockSurface (screen);
}

#define SQR(x) ((x)*(x))

static double
sim_bobs (struct bob *bobs, size_t num_bobs,
          double t0, double t1)
{
    double dt = 0.002;
    double G = 0.5;
    double t = t0;

    if (dt*10 &lt; (t1 - t0) &amp;&amp; 0)
        dt = (t1 - t0) / 10.0;

    while (t &lt; t1) {
        size_t i, j;

        for (i=0; i&lt;num_bobs; i++) {
            double theta = (i+0.5) / MAX_BOBS;
            double f = 0.3;
            bobs[i].focus = f + (0.96-f)*0.5*(1 + cos(3.141*t*(1-theta)));
            bobs[i].accel.x = (0.5-bobs[i].pos.x)*0.0;
            bobs[i].accel.y = (0.5-bobs[i].pos.y)*0.0;
        }

        /* Basic mass attraction forces. */
        for (i=0; i&lt;num_bobs; i++) {
            struct bob *p = bobs + i;
            for (j=i+1; j&lt;num_bobs; j++) {
                struct bob *q = bobs + j;
                double dx = q-&gt;pos.x - p-&gt;pos.x;
                double dy = q-&gt;pos.y - p-&gt;pos.y;
                double dist2 = SQR(dx) + SQR(dy);
                double f = G / dist2;

                if ((i^j) &amp; 1) {
                    f *= -1;
                }

                p-&gt;accel.x += dx*f*q-&gt;mass;
                p-&gt;accel.y += dy*f*q-&gt;mass;
                q-&gt;accel.x -= dx*f*p-&gt;mass;
                q-&gt;accel.y -= dy*f*p-&gt;mass;
            }
        }


        /* Integrate one step forwards. */
        for (i=0; i&lt;num_bobs; i++) {
            struct bob *p = bobs + i;

            p-&gt;accel.x = p-&gt;accel.x;
            p-&gt;accel.y = p-&gt;accel.y;

            p-&gt;vel.x += dt*p-&gt;accel.x;
            p-&gt;vel.y += dt*p-&gt;accel.y;

            p-&gt;vel.x = p-&gt;vel.x;
            p-&gt;vel.y = p-&gt;vel.y;

            p-&gt;pos.x = p-&gt;pos.x + dt*p-&gt;vel.x;
            p-&gt;pos.y = p-&gt;pos.y + dt*p-&gt;vel.y;

        }

        /* Apply position constraints. */
        for (i=0; i&lt;num_bobs; i++) {
            double eps = 0.0;
            struct bob *p = bobs + i;

            /* Bounce off each other after allowed overlap. */
            for (j=i+1; j&lt;num_bobs; j++) {
                struct bob *q = bobs + j;
                double dx = q-&gt;pos.x - p-&gt;pos.x;
                double dy = q-&gt;pos.y - p-&gt;pos.y;
                double dist = sqrt(SQR(dx) + SQR(dy));
                double overlap = p-&gt;radius*p-&gt;focus + q-&gt;radius*q-&gt;focus - dist - 0.02;

                if (overlap &lt; 0.0)
                    continue;
                p-&gt;pos.x -= dx*overlap/dist;
                p-&gt;pos.y -= dy*overlap/dist;
                q-&gt;pos.x += dx*overlap/dist;
                q-&gt;pos.y += dy*overlap/dist;

                /* Swap velocity vectors, preserve momentum. */
                {
                    double scale;
                    struct vector tmp = p-&gt;vel;
                    p-&gt;vel = q-&gt;vel;
                    q-&gt;vel = tmp;

                    scale = q-&gt;mass/p-&gt;mass;
                    p-&gt;vel.x *= scale;
                    p-&gt;vel.y *= scale;
                    scale = p-&gt;mass/q-&gt;mass;
                    q-&gt;vel.x *= scale;
                    q-&gt;vel.y *= scale;
                }
            }

            /* Bounce off walls */
            if (p-&gt;pos.x &gt; 1+eps - p-&gt;radius*p-&gt;focus) {
                p-&gt;pos.x = 1+eps - p-&gt;radius*p-&gt;focus;
                p-&gt;vel.x *= -1;
            }
            if (p-&gt;pos.x &lt; 0-eps + p-&gt;radius*p-&gt;focus) {
                p-&gt;pos.x = 0-eps + p-&gt;radius*p-&gt;focus;
                p-&gt;vel.x *= -1;
            }
            if (p-&gt;pos.y &gt; 1+eps - p-&gt;radius*p-&gt;focus) {
                p-&gt;pos.y = 1+eps - p-&gt;radius*p-&gt;focus;
                p-&gt;vel.y *= -1;
            }
            if (p-&gt;pos.y &lt; 0-eps + p-&gt;radius*p-&gt;focus) {
                p-&gt;pos.y = 0-eps + p-&gt;radius*p-&gt;focus;
                p-&gt;vel.y *= -1;
            }

        }


        t += dt;
        if (t + dt &gt;= t1)
            dt = t1 - t + 1e-6;
    }

    return t1;
}

static void
push_expose ()
{
    SDL_Event event[1];
    event-&gt;type = SDL_VIDEOEXPOSE;
    if (SDL_PushEvent (event) != 0) {
        fprintf (stderr, "Failed to push an expose event: %s\n",
                 SDL_GetError ());
    }
}

static void
on_expose (struct bob *bobs, size_t num_bobs)
{
    SDL_Surface *screen = SDL_GetVideoSurface ();

    SDL_FillRect (screen, NULL,
                  SDL_MapRGBA (screen-&gt;format,
                               0,0,0,SDL_ALPHA_OPAQUE));

    if (BLIT_BOBS_USING_CAIRO)
        blit_bobs_using_cairo (bobs, num_bobs);
    else
        blit_bobs_using_sdl (bobs, num_bobs);

    SDL_Flip (screen);

    push_expose ();             /* Schedule another expose soon, */
}

static void
event_loop (unsigned flags, int width, int height)
{
    struct bob bobs[MAX_BOBS];
    size_t num_bobs = MAX_BOBS;

    double t0 = SDL_GetTicks () / 1000.0; /* Current simulation time.. */
    double t1;                  /* Next simulation time. */
    SDL_Event event[1];

    init_bobs (bobs, num_bobs);

    event-&gt;resize.type = SDL_VIDEORESIZE;
    event-&gt;resize.w = width;
    event-&gt;resize.h = height;
    SDL_PushEvent (event);

    while (SDL_WaitEvent (event)) {
        switch (event-&gt;type) {
        case SDL_VIDEORESIZE:
            if (SDL_SetVideoMode (event-&gt;resize.w,
                                  event-&gt;resize.h,
                                  32, flags) == NULL)
            {
                fprintf (stderr, "Failed to set video mode: %s\n",
                         SDL_GetError ());
                exit (1);
            }
            alloc_bobs (bobs, num_bobs);
            render_bobs (bobs, num_bobs);
            /* fallthrough  */

        case SDL_VIDEOEXPOSE:
            t1 = SDL_GetTicks () / 1000.0;
            render_bobs (bobs, num_bobs);
            t0 = sim_bobs (bobs, num_bobs, t0, t1);
            on_expose (bobs, num_bobs);
            break;

        case SDL_KEYDOWN:
            if (event-&gt;key.keysym.sym == SDLK_q)
                return;
        }
    }
    fprintf (stderr, "WaitEvent failed: %s\n", SDL_GetError ());
}

int
main()
{
    int width = 600;
    int height = 600;
    int flags = SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE;

    if (SDL_Init (flags) &lt; 0) {
        fprintf (stderr, "Failed to initialise SDL: %s\n",
                 SDL_GetError ());
        exit (1);
    }
    atexit (SDL_Quit);

    if (1) {
        event_loop (
            SDL_SWSURFACE | SDL_RESIZABLE,
            width, height);
    }
    else {
        event_loop (
            SDL_HWSURFACE |
            SDL_FULLSCREEN |
            SDL_DOUBLEBUF,
            width, height);
    }
    return 0;
}
</code></pre></td></tr></table>
</div> <!-- class=content -->
<div class='footer'>generated  by cgit v0.8.3-6-g21f6 at 2010-02-04 22:01:22 (GMT)</div>
</div> <!-- id=cgit -->
</body>
</html>
