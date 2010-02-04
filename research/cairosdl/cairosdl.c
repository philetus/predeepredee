<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>
<head>
<title>~joonas/cairosdl - Unnamed repository; edit this file to name it for gitweb.</title>
<meta name='generator' content='cgit v0.8.3-6-g21f6'/>
<meta name='robots' content='index, nofollow'/>
<link rel='stylesheet' type='text/css' href='http://cgit.freedesktop.org/cgit.css'/>
<link rel='alternate' title='Atom feed' href='http://cgit.freedesktop.org/~joonas/cairosdl/atom/cairosdl.c?h=demos' type='application/atom+xml'/>
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
<a href='/~joonas/cairosdl/?h=demos'>summary</a><a href='/~joonas/cairosdl/refs/?h=demos'>refs</a><a href='/~joonas/cairosdl/log/?h=demos'>log</a><a class='active' href='/~joonas/cairosdl/tree/?h=demos'>tree</a><a href='/~joonas/cairosdl/commit/?h=demos'>commit</a><a href='/~joonas/cairosdl/diff/?h=demos'>diff</a></td><td class='form'><form class='right' method='get' action='/~joonas/cairosdl/log/cairosdl.c'>
<input type='hidden' name='h' value='demos'/><select name='qt'>
<option value='grep'>log msg</option>
<option value='author'>author</option>
<option value='committer'>committer</option>
</select>
<input class='txt' type='text' size='10' name='q' value=''/>
<input type='submit' value='search'/>
</form>
</td></tr></table>
<div class='content'>path: <a href='/~joonas/cairosdl/tree/?h=demos'>root</a>/<a href='/~joonas/cairosdl/tree/cairosdl.c?h=demos'>cairosdl.c</a> (<a href='/~joonas/cairosdl/plain/cairosdl.c?h=demos'>plain</a>)<br/>blob: fcfa8fa566d9ddc8067653dc19374c669e175c43
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
<a class='no' id='n460' name='n460' href='#n460'>460</a>
<a class='no' id='n461' name='n461' href='#n461'>461</a>
<a class='no' id='n462' name='n462' href='#n462'>462</a>
<a class='no' id='n463' name='n463' href='#n463'>463</a>
<a class='no' id='n464' name='n464' href='#n464'>464</a>
<a class='no' id='n465' name='n465' href='#n465'>465</a>
<a class='no' id='n466' name='n466' href='#n466'>466</a>
<a class='no' id='n467' name='n467' href='#n467'>467</a>
<a class='no' id='n468' name='n468' href='#n468'>468</a>
<a class='no' id='n469' name='n469' href='#n469'>469</a>
<a class='no' id='n470' name='n470' href='#n470'>470</a>
<a class='no' id='n471' name='n471' href='#n471'>471</a>
<a class='no' id='n472' name='n472' href='#n472'>472</a>
<a class='no' id='n473' name='n473' href='#n473'>473</a>
<a class='no' id='n474' name='n474' href='#n474'>474</a>
<a class='no' id='n475' name='n475' href='#n475'>475</a>
<a class='no' id='n476' name='n476' href='#n476'>476</a>
<a class='no' id='n477' name='n477' href='#n477'>477</a>
<a class='no' id='n478' name='n478' href='#n478'>478</a>
<a class='no' id='n479' name='n479' href='#n479'>479</a>
<a class='no' id='n480' name='n480' href='#n480'>480</a>
<a class='no' id='n481' name='n481' href='#n481'>481</a>
<a class='no' id='n482' name='n482' href='#n482'>482</a>
<a class='no' id='n483' name='n483' href='#n483'>483</a>
<a class='no' id='n484' name='n484' href='#n484'>484</a>
<a class='no' id='n485' name='n485' href='#n485'>485</a>
<a class='no' id='n486' name='n486' href='#n486'>486</a>
<a class='no' id='n487' name='n487' href='#n487'>487</a>
<a class='no' id='n488' name='n488' href='#n488'>488</a>
<a class='no' id='n489' name='n489' href='#n489'>489</a>
<a class='no' id='n490' name='n490' href='#n490'>490</a>
<a class='no' id='n491' name='n491' href='#n491'>491</a>
<a class='no' id='n492' name='n492' href='#n492'>492</a>
<a class='no' id='n493' name='n493' href='#n493'>493</a>
<a class='no' id='n494' name='n494' href='#n494'>494</a>
<a class='no' id='n495' name='n495' href='#n495'>495</a>
<a class='no' id='n496' name='n496' href='#n496'>496</a>
<a class='no' id='n497' name='n497' href='#n497'>497</a>
<a class='no' id='n498' name='n498' href='#n498'>498</a>
<a class='no' id='n499' name='n499' href='#n499'>499</a>
<a class='no' id='n500' name='n500' href='#n500'>500</a>
<a class='no' id='n501' name='n501' href='#n501'>501</a>
<a class='no' id='n502' name='n502' href='#n502'>502</a>
<a class='no' id='n503' name='n503' href='#n503'>503</a>
<a class='no' id='n504' name='n504' href='#n504'>504</a>
<a class='no' id='n505' name='n505' href='#n505'>505</a>
<a class='no' id='n506' name='n506' href='#n506'>506</a>
<a class='no' id='n507' name='n507' href='#n507'>507</a>
<a class='no' id='n508' name='n508' href='#n508'>508</a>
<a class='no' id='n509' name='n509' href='#n509'>509</a>
<a class='no' id='n510' name='n510' href='#n510'>510</a>
<a class='no' id='n511' name='n511' href='#n511'>511</a>
<a class='no' id='n512' name='n512' href='#n512'>512</a>
<a class='no' id='n513' name='n513' href='#n513'>513</a>
<a class='no' id='n514' name='n514' href='#n514'>514</a>
<a class='no' id='n515' name='n515' href='#n515'>515</a>
<a class='no' id='n516' name='n516' href='#n516'>516</a>
<a class='no' id='n517' name='n517' href='#n517'>517</a>
<a class='no' id='n518' name='n518' href='#n518'>518</a>
<a class='no' id='n519' name='n519' href='#n519'>519</a>
<a class='no' id='n520' name='n520' href='#n520'>520</a>
<a class='no' id='n521' name='n521' href='#n521'>521</a>
<a class='no' id='n522' name='n522' href='#n522'>522</a>
<a class='no' id='n523' name='n523' href='#n523'>523</a>
<a class='no' id='n524' name='n524' href='#n524'>524</a>
<a class='no' id='n525' name='n525' href='#n525'>525</a>
<a class='no' id='n526' name='n526' href='#n526'>526</a>
<a class='no' id='n527' name='n527' href='#n527'>527</a>
<a class='no' id='n528' name='n528' href='#n528'>528</a>
<a class='no' id='n529' name='n529' href='#n529'>529</a>
<a class='no' id='n530' name='n530' href='#n530'>530</a>
<a class='no' id='n531' name='n531' href='#n531'>531</a>
<a class='no' id='n532' name='n532' href='#n532'>532</a>
<a class='no' id='n533' name='n533' href='#n533'>533</a>
<a class='no' id='n534' name='n534' href='#n534'>534</a>
<a class='no' id='n535' name='n535' href='#n535'>535</a>
<a class='no' id='n536' name='n536' href='#n536'>536</a>
<a class='no' id='n537' name='n537' href='#n537'>537</a>
<a class='no' id='n538' name='n538' href='#n538'>538</a>
<a class='no' id='n539' name='n539' href='#n539'>539</a>
<a class='no' id='n540' name='n540' href='#n540'>540</a>
<a class='no' id='n541' name='n541' href='#n541'>541</a>
<a class='no' id='n542' name='n542' href='#n542'>542</a>
<a class='no' id='n543' name='n543' href='#n543'>543</a>
<a class='no' id='n544' name='n544' href='#n544'>544</a>
<a class='no' id='n545' name='n545' href='#n545'>545</a>
<a class='no' id='n546' name='n546' href='#n546'>546</a>
<a class='no' id='n547' name='n547' href='#n547'>547</a>
<a class='no' id='n548' name='n548' href='#n548'>548</a>
<a class='no' id='n549' name='n549' href='#n549'>549</a>
<a class='no' id='n550' name='n550' href='#n550'>550</a>
<a class='no' id='n551' name='n551' href='#n551'>551</a>
<a class='no' id='n552' name='n552' href='#n552'>552</a>
<a class='no' id='n553' name='n553' href='#n553'>553</a>
<a class='no' id='n554' name='n554' href='#n554'>554</a>
<a class='no' id='n555' name='n555' href='#n555'>555</a>
<a class='no' id='n556' name='n556' href='#n556'>556</a>
<a class='no' id='n557' name='n557' href='#n557'>557</a>
<a class='no' id='n558' name='n558' href='#n558'>558</a>
<a class='no' id='n559' name='n559' href='#n559'>559</a>
<a class='no' id='n560' name='n560' href='#n560'>560</a>
<a class='no' id='n561' name='n561' href='#n561'>561</a>
<a class='no' id='n562' name='n562' href='#n562'>562</a>
<a class='no' id='n563' name='n563' href='#n563'>563</a>
<a class='no' id='n564' name='n564' href='#n564'>564</a>
<a class='no' id='n565' name='n565' href='#n565'>565</a>
<a class='no' id='n566' name='n566' href='#n566'>566</a>
<a class='no' id='n567' name='n567' href='#n567'>567</a>
<a class='no' id='n568' name='n568' href='#n568'>568</a>
<a class='no' id='n569' name='n569' href='#n569'>569</a>
<a class='no' id='n570' name='n570' href='#n570'>570</a>
<a class='no' id='n571' name='n571' href='#n571'>571</a>
<a class='no' id='n572' name='n572' href='#n572'>572</a>
<a class='no' id='n573' name='n573' href='#n573'>573</a>
<a class='no' id='n574' name='n574' href='#n574'>574</a>
<a class='no' id='n575' name='n575' href='#n575'>575</a>
<a class='no' id='n576' name='n576' href='#n576'>576</a>
<a class='no' id='n577' name='n577' href='#n577'>577</a>
<a class='no' id='n578' name='n578' href='#n578'>578</a>
<a class='no' id='n579' name='n579' href='#n579'>579</a>
<a class='no' id='n580' name='n580' href='#n580'>580</a>
<a class='no' id='n581' name='n581' href='#n581'>581</a>
<a class='no' id='n582' name='n582' href='#n582'>582</a>
<a class='no' id='n583' name='n583' href='#n583'>583</a>
<a class='no' id='n584' name='n584' href='#n584'>584</a>
<a class='no' id='n585' name='n585' href='#n585'>585</a>
<a class='no' id='n586' name='n586' href='#n586'>586</a>
<a class='no' id='n587' name='n587' href='#n587'>587</a>
<a class='no' id='n588' name='n588' href='#n588'>588</a>
<a class='no' id='n589' name='n589' href='#n589'>589</a>
<a class='no' id='n590' name='n590' href='#n590'>590</a>
<a class='no' id='n591' name='n591' href='#n591'>591</a>
<a class='no' id='n592' name='n592' href='#n592'>592</a>
<a class='no' id='n593' name='n593' href='#n593'>593</a>
<a class='no' id='n594' name='n594' href='#n594'>594</a>
<a class='no' id='n595' name='n595' href='#n595'>595</a>
<a class='no' id='n596' name='n596' href='#n596'>596</a>
<a class='no' id='n597' name='n597' href='#n597'>597</a>
<a class='no' id='n598' name='n598' href='#n598'>598</a>
<a class='no' id='n599' name='n599' href='#n599'>599</a>
<a class='no' id='n600' name='n600' href='#n600'>600</a>
<a class='no' id='n601' name='n601' href='#n601'>601</a>
<a class='no' id='n602' name='n602' href='#n602'>602</a>
<a class='no' id='n603' name='n603' href='#n603'>603</a>
<a class='no' id='n604' name='n604' href='#n604'>604</a>
<a class='no' id='n605' name='n605' href='#n605'>605</a>
<a class='no' id='n606' name='n606' href='#n606'>606</a>
<a class='no' id='n607' name='n607' href='#n607'>607</a>
<a class='no' id='n608' name='n608' href='#n608'>608</a>
<a class='no' id='n609' name='n609' href='#n609'>609</a>
<a class='no' id='n610' name='n610' href='#n610'>610</a>
<a class='no' id='n611' name='n611' href='#n611'>611</a>
<a class='no' id='n612' name='n612' href='#n612'>612</a>
<a class='no' id='n613' name='n613' href='#n613'>613</a>
<a class='no' id='n614' name='n614' href='#n614'>614</a>
<a class='no' id='n615' name='n615' href='#n615'>615</a>
<a class='no' id='n616' name='n616' href='#n616'>616</a>
<a class='no' id='n617' name='n617' href='#n617'>617</a>
<a class='no' id='n618' name='n618' href='#n618'>618</a>
<a class='no' id='n619' name='n619' href='#n619'>619</a>
<a class='no' id='n620' name='n620' href='#n620'>620</a>
<a class='no' id='n621' name='n621' href='#n621'>621</a>
<a class='no' id='n622' name='n622' href='#n622'>622</a>
<a class='no' id='n623' name='n623' href='#n623'>623</a>
<a class='no' id='n624' name='n624' href='#n624'>624</a>
<a class='no' id='n625' name='n625' href='#n625'>625</a>
<a class='no' id='n626' name='n626' href='#n626'>626</a>
<a class='no' id='n627' name='n627' href='#n627'>627</a>
<a class='no' id='n628' name='n628' href='#n628'>628</a>
<a class='no' id='n629' name='n629' href='#n629'>629</a>
<a class='no' id='n630' name='n630' href='#n630'>630</a>
<a class='no' id='n631' name='n631' href='#n631'>631</a>
<a class='no' id='n632' name='n632' href='#n632'>632</a>
<a class='no' id='n633' name='n633' href='#n633'>633</a>
<a class='no' id='n634' name='n634' href='#n634'>634</a>
<a class='no' id='n635' name='n635' href='#n635'>635</a>
<a class='no' id='n636' name='n636' href='#n636'>636</a>
<a class='no' id='n637' name='n637' href='#n637'>637</a>
<a class='no' id='n638' name='n638' href='#n638'>638</a>
<a class='no' id='n639' name='n639' href='#n639'>639</a>
<a class='no' id='n640' name='n640' href='#n640'>640</a>
<a class='no' id='n641' name='n641' href='#n641'>641</a>
<a class='no' id='n642' name='n642' href='#n642'>642</a>
<a class='no' id='n643' name='n643' href='#n643'>643</a>
<a class='no' id='n644' name='n644' href='#n644'>644</a>
<a class='no' id='n645' name='n645' href='#n645'>645</a>
<a class='no' id='n646' name='n646' href='#n646'>646</a>
<a class='no' id='n647' name='n647' href='#n647'>647</a>
<a class='no' id='n648' name='n648' href='#n648'>648</a>
<a class='no' id='n649' name='n649' href='#n649'>649</a>
<a class='no' id='n650' name='n650' href='#n650'>650</a>
<a class='no' id='n651' name='n651' href='#n651'>651</a>
<a class='no' id='n652' name='n652' href='#n652'>652</a>
<a class='no' id='n653' name='n653' href='#n653'>653</a>
<a class='no' id='n654' name='n654' href='#n654'>654</a>
<a class='no' id='n655' name='n655' href='#n655'>655</a>
<a class='no' id='n656' name='n656' href='#n656'>656</a>
<a class='no' id='n657' name='n657' href='#n657'>657</a>
<a class='no' id='n658' name='n658' href='#n658'>658</a>
<a class='no' id='n659' name='n659' href='#n659'>659</a>
<a class='no' id='n660' name='n660' href='#n660'>660</a>
<a class='no' id='n661' name='n661' href='#n661'>661</a>
<a class='no' id='n662' name='n662' href='#n662'>662</a>
<a class='no' id='n663' name='n663' href='#n663'>663</a>
<a class='no' id='n664' name='n664' href='#n664'>664</a>
<a class='no' id='n665' name='n665' href='#n665'>665</a>
<a class='no' id='n666' name='n666' href='#n666'>666</a>
<a class='no' id='n667' name='n667' href='#n667'>667</a>
<a class='no' id='n668' name='n668' href='#n668'>668</a>
<a class='no' id='n669' name='n669' href='#n669'>669</a>
<a class='no' id='n670' name='n670' href='#n670'>670</a>
<a class='no' id='n671' name='n671' href='#n671'>671</a>
<a class='no' id='n672' name='n672' href='#n672'>672</a>
<a class='no' id='n673' name='n673' href='#n673'>673</a>
<a class='no' id='n674' name='n674' href='#n674'>674</a>
<a class='no' id='n675' name='n675' href='#n675'>675</a>
<a class='no' id='n676' name='n676' href='#n676'>676</a>
<a class='no' id='n677' name='n677' href='#n677'>677</a>
<a class='no' id='n678' name='n678' href='#n678'>678</a>
<a class='no' id='n679' name='n679' href='#n679'>679</a>
<a class='no' id='n680' name='n680' href='#n680'>680</a>
<a class='no' id='n681' name='n681' href='#n681'>681</a>
<a class='no' id='n682' name='n682' href='#n682'>682</a>
<a class='no' id='n683' name='n683' href='#n683'>683</a>
<a class='no' id='n684' name='n684' href='#n684'>684</a>
<a class='no' id='n685' name='n685' href='#n685'>685</a>
<a class='no' id='n686' name='n686' href='#n686'>686</a>
<a class='no' id='n687' name='n687' href='#n687'>687</a>
<a class='no' id='n688' name='n688' href='#n688'>688</a>
<a class='no' id='n689' name='n689' href='#n689'>689</a>
<a class='no' id='n690' name='n690' href='#n690'>690</a>
<a class='no' id='n691' name='n691' href='#n691'>691</a>
<a class='no' id='n692' name='n692' href='#n692'>692</a>
<a class='no' id='n693' name='n693' href='#n693'>693</a>
<a class='no' id='n694' name='n694' href='#n694'>694</a>
<a class='no' id='n695' name='n695' href='#n695'>695</a>
<a class='no' id='n696' name='n696' href='#n696'>696</a>
<a class='no' id='n697' name='n697' href='#n697'>697</a>
<a class='no' id='n698' name='n698' href='#n698'>698</a>
<a class='no' id='n699' name='n699' href='#n699'>699</a>
<a class='no' id='n700' name='n700' href='#n700'>700</a>
</pre></td>
<td class='lines'><pre><code>/*
 * Copyright (c) 2009  M Joonas Pihlaja
 * Copyright (c) 2009  Paul-Virak Khuong
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#include &lt;assert.h&gt;
#include "cairosdl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forward references */
static void
_cairosdl_blit_and_unpremultiply (
    void       *target_buffer,
    size_t      target_stride,
    void const *source_buffer,
    size_t      source_stride,
    int         width,
    int         height);

static void
_cairosdl_blit_and_premultiply (
    void       *target_buffer,
    size_t      target_stride,
    void const *source_buffer,
    size_t      source_stride,
    int         width,
    int         height);

/*
 * Surface functions
 */

/* We're hanging the SDL_Surface as a user datum on the
 * cairo_surface_t representing it using this key.  Turns out we need
 * to initialise it for C++. */
static cairo_user_data_key_t const CAIROSDL_TARGET_KEY[1] = {{1}};

static void
sdl_surface_destroy_func (void *param)
{
    SDL_Surface *sdl_surface = (SDL_Surface *)param;
    if (sdl_surface != NULL)
        SDL_FreeSurface (sdl_surface);
}

cairo_surface_t *
cairosdl_surface_create (
    SDL_Surface *sdl_surface)
{
    cairo_surface_t *target;
    cairo_format_t format;
    int is_dirty;

    /* Cairo only supports a limited number of pixels formats.  Make
     * sure the surface format is compatible. */
    if (sdl_surface-&gt;format-&gt;BytesPerPixel != 4 ||
        sdl_surface-&gt;format-&gt;BitsPerPixel != 32)
        goto unsupported_format;

    if (sdl_surface-&gt;format-&gt;Rmask != CAIROSDL_RMASK ||
        sdl_surface-&gt;format-&gt;Gmask != CAIROSDL_GMASK ||
        sdl_surface-&gt;format-&gt;Bmask != CAIROSDL_BMASK)
        goto unsupported_format;

    switch (sdl_surface-&gt;format-&gt;Amask) {
    case CAIROSDL_AMASK:
        format = CAIRO_FORMAT_ARGB32;
        break;
    case 0:
        format = CAIRO_FORMAT_RGB24;
        break;
    default:
        goto unsupported_format;
    }

    /* Make the target point to either the SDL_Surface's data itself
     * or a shadow image surface if we need to unpremultiply pixels. */
    if (format == CAIRO_FORMAT_RGB24) {
        /* The caller is expected to have locked the surface (_if_ it
         * needs locking) so that sdl_surface-&gt;pixels is valid and
         * constant for the lifetime of the cairo_surface_t.  However,
         * we're told not to call any OS functions when a surface is
         * locked, so we really shouldn't call
         * cairo_image_surface_create () as it will malloc, so really
         * if the surface needs locking this shouldn't be used.
         *
         * However, it turns out malloc is actually safe on many (all?)
         * platforms so we'll just go ahead anyway. */
        unsigned char *data = (unsigned char*)(sdl_surface-&gt;pixels);
        target = cairo_image_surface_create_for_data (data,
                                                      format,
                                                      sdl_surface-&gt;w,
                                                      sdl_surface-&gt;h,
                                                      sdl_surface-&gt;pitch);
        is_dirty = 0;
    }
    else {
        /* Need a shadow image surface. */
        target = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                             sdl_surface-&gt;w,
                                             sdl_surface-&gt;h);
        is_dirty = 1;
    }

    if (cairo_surface_status (target) == CAIRO_STATUS_SUCCESS) {
        sdl_surface-&gt;refcount++;
        cairo_surface_set_user_data (target,
                                     CAIROSDL_TARGET_KEY,
                                     sdl_surface,
                                     sdl_surface_destroy_func);

        if (is_dirty)
            cairosdl_surface_mark_dirty (target);
    }

    return target;

 unsupported_format:
    /* Nasty kludge to get a cairo surface in CAIRO_INVALID_FORMAT
     * state. */
    return cairo_image_surface_create (
        (cairo_format_t)-1, 0, 0);
}

SDL_Surface *
cairosdl_surface_get_target (
    cairo_surface_t *surface)
{
    void *udata = cairo_surface_get_user_data (surface, CAIROSDL_TARGET_KEY);
    return (SDL_Surface*)(udata);
}

static cairo_status_t
_cairosdl_surface_obtain_SDL_buffer(
    cairo_surface_t *surface,
    unsigned char  **OUT_buffer,
    size_t          *OUT_stride,
    size_t          *OUT_width,
    size_t          *OUT_height)
{
    SDL_Surface *sdl_surface = cairosdl_surface_get_target (surface);
    if (sdl_surface == NULL)
        return CAIRO_STATUS_NULL_POINTER;

    if (OUT_buffer)
        *OUT_buffer = (unsigned char *)(sdl_surface-&gt;pixels);
    if (OUT_stride)
        *OUT_stride = sdl_surface-&gt;pitch;
    if (OUT_width)
        *OUT_width = sdl_surface-&gt;w;
    if (OUT_height)
        *OUT_height = sdl_surface-&gt;h;
    return CAIRO_STATUS_SUCCESS;
}

static cairo_status_t
_cairosdl_surface_obtain_shadow_buffer(
    cairo_surface_t *surface,
    unsigned char  **OUT_buffer,
    size_t          *OUT_stride,
    size_t          *OUT_width,
    size_t          *OUT_height)
{
    cairo_format_t format;

    if (cairo_surface_get_type (surface) != CAIRO_SURFACE_TYPE_IMAGE)
        return CAIRO_STATUS_SURFACE_TYPE_MISMATCH;

    format = cairo_image_surface_get_format (surface);
    if (format != CAIRO_FORMAT_ARGB32)
        return CAIRO_STATUS_INVALID_FORMAT;

    if (OUT_buffer != NULL)
        *OUT_buffer = cairo_image_surface_get_data (surface);
    if (OUT_stride != NULL)
        *OUT_stride = cairo_image_surface_get_stride (surface);
    if (OUT_width != NULL)
        *OUT_width = cairo_image_surface_get_width (surface);
    if (OUT_height != NULL)
        *OUT_height = cairo_image_surface_get_height (surface);
    return CAIRO_STATUS_SUCCESS;
}

void
cairosdl_surface_flush_rects (
    cairo_surface_t *surface,
    int              num_rects,
    SDL_Rect const  *rects)
{
    unsigned char *source_bytes;
    size_t source_stride;
    size_t source_width;
    size_t source_height;

    unsigned char *target_bytes;
    size_t target_stride;
    size_t target_width;
    size_t target_height;

    int width, height;
    cairo_status_t status;

    if (num_rects &lt;= 0)
        return;

    cairo_surface_flush (surface);

    status = _cairosdl_surface_obtain_SDL_buffer (surface,
                                                  &amp;target_bytes,
                                                  &amp;target_stride,
                                                  &amp;target_width,
                                                  &amp;target_height);
    if (status != CAIRO_STATUS_SUCCESS)
        return;                 /* no buffer -&gt; nothing to do */

    status = _cairosdl_surface_obtain_shadow_buffer (surface,
                                                     &amp;source_bytes,
                                                     &amp;source_stride,
                                                     &amp;source_width,
                                                     &amp;source_height);
    if (status != CAIRO_STATUS_SUCCESS)
        return;                 /* no buffer -&gt; nothing to do */

    width = source_width &lt; target_width ? source_width : target_width;
    height = source_height &lt; target_height ? source_height : target_height;
    assert(width &gt;= 0 &amp;&amp; height &gt;= 0);

    while (num_rects-- &gt; 0) {
        Sint32 x = rects-&gt;x;
        Sint32 y = rects-&gt;y;
        Sint32 w = rects-&gt;w;
        Sint32 h = rects-&gt;h;
        rects++;

        if (x &lt;= 0) { w += x; x = 0; }
        if (y &lt;= 0) { h += y; y = 0; }
        if (x + w &gt;= width) w = width - x;
        if (y + h &gt;= height) h = height - y;

        _cairosdl_blit_and_unpremultiply (
            target_bytes + target_stride*y + x, target_stride,
            source_bytes + source_stride*y + x, source_stride,
            w, h);
    }
}

void
cairosdl_surface_mark_dirty_rects (
    cairo_surface_t *surface,
    int              num_rects,
    SDL_Rect const  *rects)
{
    unsigned char *source_bytes = NULL;
    size_t source_stride = 0;
    size_t source_width = 32767;
    size_t source_height = 32767;

    unsigned char *target_bytes = NULL;
    size_t target_stride = 0;
    size_t target_width = 32767;
    size_t target_height = 32767;

    int width, height;
    cairo_status_t status;
    int have_buffers = 1;

    if (num_rects &lt;= 0)
        return;

    status = _cairosdl_surface_obtain_SDL_buffer (surface,
                                                  &amp;source_bytes,
                                                  &amp;source_stride,
                                                  &amp;source_width,
                                                  &amp;source_height);
    if (status != CAIRO_STATUS_SUCCESS)
        have_buffers = 0;

    status = _cairosdl_surface_obtain_shadow_buffer (surface,
                                                     &amp;target_bytes,
                                                     &amp;target_stride,
                                                     &amp;target_width,
                                                     &amp;target_height);
    if (status != CAIRO_STATUS_SUCCESS)
        have_buffers = 0;

    width = source_width &lt; target_width ? source_width : target_width;
    height = source_height &lt; target_height ? source_height : target_height;
    assert(width &gt;= 0 &amp;&amp; height &gt;= 0);

    while (num_rects-- &gt; 0) {
        Sint32 x = rects-&gt;x;
        Sint32 y = rects-&gt;y;
        Sint32 w = rects-&gt;w;
        Sint32 h = rects-&gt;h;
        rects++;

        if (x &lt;= 0) { w += x; x = 0; }
        if (y &lt;= 0) { h += y; y = 0; }
        if (x &gt;= width || y &gt;= height) continue;
        if (x + w &gt;= width) w = width - x;
        if (y + h &gt;= height) h = height - y;
        if (w &lt;= 0 || h &lt;= 0) continue;

        if (have_buffers) {
            _cairosdl_blit_and_premultiply (
                target_bytes + target_stride*y + x, target_stride,
                source_bytes + source_stride*y + x, source_stride,
                w, h);
        }

        cairo_surface_mark_dirty_rectangle (surface, x, y, w, h);
    }
}

static SDL_Rect
make_rect(int x, int y, int w, int h)
{
    static SDL_Rect const empty_rect = {0,0,0,0};
    SDL_Rect r;

    /* Clamp the rect to [0,32768). */
    if (w &lt;= 0 || h &lt;= 0)
        return empty_rect;
    if (x &lt; 0) { w += x; x = 0; }
    if (y &lt; 0) { h += y; y = 0; }
    if ((unsigned)w &gt; 32767) w = 32767;
    if ((unsigned)h &gt; 32767) h = 32767;

    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}

void
cairosdl_surface_flush_rect (
    cairo_surface_t *surface,
    int              x,
    int              y,
    int              w,
    int              h)
{
    SDL_Rect rect = make_rect(x, y, w, h);
    cairosdl_surface_flush_rects (surface, 1, &amp;rect);
}

void
cairosdl_surface_mark_dirty_rect (
    cairo_surface_t *surface,
    int              x,
    int              y,
    int              w,
    int              h)
{
    SDL_Rect rect = make_rect(x, y, w, h);
    cairosdl_surface_mark_dirty_rects (surface, 1, &amp;rect);
}

void
cairosdl_surface_flush (cairo_surface_t *surface)
{
    cairosdl_surface_flush_rect (surface, 0, 0, 32767, 32767);
}

void
cairosdl_surface_mark_dirty (cairo_surface_t *surface)
{
    cairosdl_surface_mark_dirty_rect (surface, 0, 0, 32767, 32767);
}

/*
 * Context functions for convenience.
 */

SDL_Surface *
cairosdl_get_target (cairo_t *cr)
{
    return cairosdl_surface_get_target (cairo_get_target (cr));
}

cairo_t *
cairosdl_create (SDL_Surface *sdl_surface)
{
    cairo_surface_t *surface = cairosdl_surface_create (sdl_surface);
    cairo_t *cr = cairo_create (surface);
    cairo_surface_destroy (surface);
    return cr;
}

void
cairosdl_destroy (cairo_t *cr)
{
    cairosdl_surface_flush (cairo_get_target (cr));
    cairo_destroy (cr);
}

/* unpremultiply-lutb.c
 *
 * A pixel premultiplier and an unpremultiplier using reciprocal
 * multiplication.  It specialises constant runs and solid runs of
 * pixels with low overhead loops and uses only a 1KB table of
 * reciprocals.
 *
 * The unpremultiplier was snarfed from
 * http://cgit.freedesktop.org/~joonas/unpremultiply
 *
 * See there for other faster or nonportable variations on
 * unpremultiply.  This one is a good all rounder that doesn't take
 * that much data space. */

/* Pixel format config for a 32 bit pixel with 8 bit components.  Only
 * the location of alpha matters.  Cairo uses ASHIFT 24. */
#define ASHIFT CAIROSDL_ASHIFT
#define RSHIFT ((24 + ASHIFT) % 32)
#define GSHIFT ((16 + ASHIFT) % 32)
#define BSHIFT (( 8 + ASHIFT) % 32)

#define AMASK (255U &lt;&lt; ASHIFT)
#define RMASK (255U &lt;&lt; RSHIFT)
#define GMASK (255U &lt;&lt; GSHIFT)
#define BMASK (255U &lt;&lt; BSHIFT)

/* Set to 1 if the input can have superluminant pixels.  Cairo doesn't
 * produce them. */
#define DO_CLAMP_INPUT 0

/* Shift x left by y bits.  Supports negative y for right shifts. */
#define SHIFT(x, y) ((y) &lt; 0 ? (x) &gt;&gt; (-(y)) : (x) &lt;&lt; (y))

#define ceil_div(a,b) ((a) + (b)-1) / (b)

/* The reciprocal_table[i] entries are defined by
 *
 * 	0		when i = 0
 *	255 / i		when i &gt; 0
 *
 * represented in fixed point format with RECIPROCAL_BITS of
 * precision and errors rounded up. */
#define RECIPROCAL_BITS 16
static unsigned const reciprocal_table[256] = {
# define R(i)  ((i) ? ceil_div(255*(1&lt;&lt;RECIPROCAL_BITS), (i)) : 0)
# define R1(i) R(i),  R(i+1),   R(i+2),   R(i+3)
# define R2(i) R1(i), R1(i+4),  R1(i+8),  R1(i+12)
# define R3(i) R2(i), R2(i+16), R2(i+32), R2(i+48)
               R3(0), R3(64),   R3(128),  R3(192)
};

/* Transfer num_pixels premultiplied pixels from src[] to dst[] and
 * unpremultiply them. */
static void
unpremultiply_row(
    unsigned       * dst,
    unsigned const * src,
    size_t           num_pixels)
{
    size_t i = 0;
    while (i &lt; num_pixels) {
	/* We want to identify long runs of constant input pixels and
	 * cache the unpremultiplied.  */
        unsigned const_in, const_out;

        /* Diff is the or of all bitwise differences from const_in
	 * during the probe period.  If it is zero after the probe
	 * period then every input pixel was identical in the
	 * probe. */
        unsigned diff = 0;

        /* Accumulator for all alphas of the probe period pixels,
	 * biased to make the sum zero if the */
        unsigned accu = -2*255;

        {
	    unsigned rgba, a, r, g, b, recip;
            rgba = const_in = src[i];
            a = (rgba &gt;&gt; ASHIFT) &amp; 255;
            accu += a;
            r = (rgba &gt;&gt; RSHIFT) &amp; 255;
            g = (rgba &gt;&gt; GSHIFT) &amp; 255;
            b = (rgba &gt;&gt; BSHIFT) &amp; 255;
            recip = reciprocal_table[a];
#if DO_CLAMP_INPUT
	    r = r &lt; a ? r : a;
	    g = g &lt; a ? g : a;
	    b = b &lt; a ? b : a;
#endif
            r = SHIFT(r * recip, RSHIFT - RECIPROCAL_BITS);
            g = SHIFT(g * recip, GSHIFT - RECIPROCAL_BITS);
            b = SHIFT(b * recip, BSHIFT - RECIPROCAL_BITS);
            dst[i] = const_out =
		(r &amp; RMASK) | (g &amp; GMASK) | (b &amp; BMASK) | (rgba &amp; AMASK);
        }

	if (i + 1 == num_pixels)
	    return;

	{
	    unsigned rgba, a, r, g, b, recip;
            rgba = src[i+1];
            a = (rgba &gt;&gt; ASHIFT) &amp; 255;
            accu += a;
            r = (rgba &gt;&gt; RSHIFT) &amp; 255;
            g = (rgba &gt;&gt; GSHIFT) &amp; 255;
            b = (rgba &gt;&gt; BSHIFT) &amp; 255;
            recip = reciprocal_table[a];
#if DO_CLAMP_INPUT
	    r = r &lt; a ? r : a;
	    g = g &lt; a ? g : a;
	    b = b &lt; a ? b : a;
#endif
            diff = rgba ^ const_in;
            r = SHIFT(r * recip, RSHIFT - RECIPROCAL_BITS);
            g = SHIFT(g * recip, GSHIFT - RECIPROCAL_BITS);
            b = SHIFT(b * recip, BSHIFT - RECIPROCAL_BITS);
            dst[i+1] =
		(r &amp; RMASK) | (g &amp; GMASK) | (b &amp; BMASK) | (rgba &amp; AMASK);
        }

        i += 2;

	/* Fall into special cases if we have special
	 * circumstances. */
        if (0 != (accu &amp; diff))
	    continue;

        if (0 == accu) {	/* a run of solid pixels. */
            unsigned in;
            while (AMASK == ((in = src[i]) &amp; AMASK)) {
                dst[i++] = in;
                if (i == num_pixels) return;
            }
        } else if (0 == diff) {	/* a run of constant pixels. */
            while (src[i] == const_in) {
                dst[i++] = const_out;
                if (i == num_pixels) return;
            }
        }
    }
}

/* Transfer num_pixels unpremultiplied pixels from src[] to dst[] and
 * premultiply them. */
static void
premultiply_row(
    unsigned       * dst,
    unsigned const * src,
    size_t           num_pixels)
{
    size_t i = 0;
    while (i &lt; num_pixels) {
	/* We want to identify long runs of constant input pixels and
	 * cache the unpremultiplied.  */
        unsigned const_in, const_out;

        /* Diff is the or of all bitwise differences from const_in
	 * during the probe period.  If it is zero after the probe
	 * period then every input pixel was identical in the
	 * probe. */
        unsigned diff = 0;

        /* Accumulator for all alphas of the probe period pixels,
	 * biased to make the sum zero if the */
        unsigned accu = -2*255;

        {
	    unsigned rgba, a, r, g, b;
            rgba = const_in = src[i];
            a = (rgba &gt;&gt; ASHIFT) &amp; 255;
            accu += a;
            r = (rgba &gt;&gt; RSHIFT) &amp; 255;
            g = (rgba &gt;&gt; GSHIFT) &amp; 255;
            b = (rgba &gt;&gt; BSHIFT) &amp; 255;

            r = SHIFT(r*a*257 + 32768, RSHIFT - 16);
            g = SHIFT(g*a*257 + 32768, GSHIFT - 16);
            b = SHIFT(b*a*257 + 32768, BSHIFT - 16);
            dst[i] = const_out =
		(r &amp; RMASK) | (g &amp; GMASK) | (b &amp; BMASK) | (rgba &amp; AMASK);
        }

	if (i + 1 == num_pixels)
	    return;

	{
	    unsigned rgba, a, r, g, b;
            rgba = src[i+1];
            a = (rgba &gt;&gt; ASHIFT) &amp; 255;
            accu += a;
            r = (rgba &gt;&gt; RSHIFT) &amp; 255;
            g = (rgba &gt;&gt; GSHIFT) &amp; 255;
            b = (rgba &gt;&gt; BSHIFT) &amp; 255;
            diff = rgba ^ const_in;

            r = SHIFT(r*a*257 + 32768, RSHIFT - 16);
            g = SHIFT(g*a*257 + 32768, GSHIFT - 16);
            b = SHIFT(b*a*257 + 32768, BSHIFT - 16);
            dst[i+1] =
		(r &amp; RMASK) | (g &amp; GMASK) | (b &amp; BMASK) | (rgba &amp; AMASK);
        }

        i += 2;

	/* Fall into special cases if we have special
	 * circumstances. */
        if (0 != (accu &amp; diff))
	    continue;

        if (0 == accu) {	/* a run of solid pixels. */
            unsigned in;
            while (AMASK == ((in = src[i]) &amp; AMASK)) {
                dst[i++] = in;
                if (i == num_pixels) return;
            }
        } else if (0 == diff) {	/* a run of constant pixels. */
            while (src[i] == const_in) {
                dst[i++] = const_out;
                if (i == num_pixels) return;
            }
        }
    }
}

static void
_cairosdl_blit_and_unpremultiply (
    void       *target_buffer,
    size_t      target_stride,
    void const *source_buffer,
    size_t      source_stride,
    int         width,
    int         height)
{
    unsigned char *target_bytes =
        (unsigned char *)target_buffer;
    unsigned char const *source_bytes =
        (unsigned char const *)source_buffer;
    if (width &lt;= 0)
        return;

    while (height-- &gt; 0) {
        unpremultiply_row ((unsigned *)target_bytes,
                           (unsigned const *)source_bytes,
                           width);

        target_bytes += target_stride;
        source_bytes += source_stride;
    }
}

static void
_cairosdl_blit_and_premultiply (
    void       *target_buffer,
    size_t      target_stride,
    void const *source_buffer,
    size_t      source_stride,
    int         width,
    int         height)
{
    unsigned char *target_bytes =
        (unsigned char *)target_buffer;
    unsigned char const *source_bytes =
        (unsigned char const *)source_buffer;
    if (width &lt;= 0)
        return;

    while (height-- &gt; 0) {
        premultiply_row ((unsigned *)target_bytes,
                         (unsigned const *)source_bytes,
                         width);

        target_bytes += target_stride;
        source_bytes += source_stride;
    }
}

#ifdef __cplusplus
}
#endif
</code></pre></td></tr></table>
</div> <!-- class=content -->
<div class='footer'>generated  by cgit v0.8.3-6-g21f6 at 2010-02-04 22:01:06 (GMT)</div>
</div> <!-- id=cgit -->
</body>
</html>
