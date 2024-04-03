To use this module, at first, a render object must be created.
    Render (object name);  

Then user should set the size of the screen by using 
    (object name).Set_Size( {value of x} , {value of y} );
   
User can then add a layer to the object by using 
    (object name).Add_Layer();

Then user can add text box to Layer object using
    (object name).Layer_List[ {number of layer} ].Add_Textbox( {Text} , {Starting_pt} , {End_pt} , {White_space} );

    {Starting_pt} , {End_pt} should be vector<int> objects , with the structure of { {value of x} , {value of y} }
        * This fist element of the map is (0,0)
        so the range of value should be (0) to ({size of map} -1)
    {Text} should be a vector<string> object with each element a single character
        e.g:{"a","4","t"}
        The size of the text should just fit in the box bounded by Starting_pt and End_pt
    {White_space} is a bool which represent wether whitespace will be inserted within elements
        {Text}={"H","e","l","l","o"}
        if {White_space}=0:
            Hello
            -----
        if {White_space}=1:
            H e l l o
            -|-|-|-|-

All the textboxes will be auto outlined:
    ┏━━━┓  
    ┃ 5 ┃  
    ┃ 6 ┃  
    ┃ 0 ┃  
    ┃ 5 ┃  
    ┗━━━┛
5605 is the inputed text

***********Due to auto outline, the map will be expanded to leave space in following way:******************

vertical:
    original map:

    A,A,A,A
    A,A,A,A
    A,A,A,A
    A,A,A,A

       ↓

    X,X,X,X
    A,A,A,A
    A,A,A,A
    A,A,A,A
    A,A,A,A
    X,X,X,X


horizontal:
    original map:

    A,A,A,A
    A,A,A,A
    A,A,A,A
    A,A,A,A

       ↓

    X,O,A,O,A,O,A,O,A,O,X
    X,O,A,O,A,O,A,O,A,O,X
    X,O,A,O,A,O,A,O,A,O,X
    X,O,A,O,A,O,A,O,A,O,X

    (X prsented extra line)
    (O presented extra space)

in total:
    original map:

%%%%%%%%%%
%%%%98%%%%
%%%%67%%%%
%%%%54%%%%
%%%%43%%%%
%%%%%%%%%%

      ↓

%%%%%%%%%%%%%%%
%%%%┏━━━━━┓%%%%  
%%%%┃ 9 8 ┃%%%% 
%%%%┃ 6 7 ┃%%%%  
%%%%┃ 5 4 ┃%%%%  
%%%%┃ 4 3 ┃%%%%  
%%%%┗━━━━━┛%%%%
%%%%%%%%%%%%%%%

if {White_space}=0, the spaces within elements will not be inserted (O)
    original map:

%%%%%%%%%%
%%%%988%%%
%%%%647%%%
%%%%534%%%
%%%%413%%%
%%%%%%%%%%

      ↓

%%%%%%%%%%%%%%%
%%%%┏━━━━━┓%%%%  
%%%%┃ 988 ┃%%%% 
%%%%┃ 647 ┃%%%%  
%%%%┃ 534 ┃%%%%  
%%%%┃ 413 ┃%%%%  
%%%%┗━━━━━┛%%%%
%%%%%%%%%%%%%%%

if {White_space}=0 was chosen, the size of text needed will be :
    ( ( {x length}-1 )*2+1 ) * {y length}
*****the actual length of every line -( ( {x length}-1 )*2+1 )- must be odd number

**********The program will handle the expansion automaticly, so the input value just need be the original value**********************

************************************The expansion have no effect on it***************************************************************

user can use following command to trigger output and print out the output
    (object_name).Render_Output();
    (object_name).Render_Print();

*After using -(object_name).Render_Output();-, previous output and all layer object within will be cleared

tips:
    user should avoid stack up any textboxes with a single layer
    user should leave at least 1 space between textboxes within a single layer for auto outlining
    element [0] of the layer list will be the layer on top