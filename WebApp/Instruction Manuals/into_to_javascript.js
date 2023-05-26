//print
console.log("Hello World!")

//declare and add
let num1=4, num2=5;
console.log("Sum: ", num1+num2);

//concatenate different data types
let num = 5, username = "s.baig", domain = "@imperial.ac.uk", type = true;
console.log(username+domain)
console.log(username+num+domain)

//create objects
let person = {
    name: "Sarim Baig",
    email: "s.baig@imperial.ac.uk",
    numOfModules: 4
   };
   console.log(person);
   console.log(person.email);

//arrays
let persons = ["Sarim", "Max", "Harry"];
console.log(persons);
console.log(persons[0]);

//if-else, loops and scopes
{
    let a = [8,2,3,-1,4,12,33,21,-12,-5,20, 101, -91];
    let count = 0;
    for (let i=0; i<a.length; i++){
    if(a[i]>=-10 && a[i]<=10){
    count++;
    }
    }
    console.log("Number of elements between -10 and 10: ", count)
}

let a = [8,2,3,-1,0,12,33,21,-12,-5,20, 101, -91];
let count = 0;
let zeros = 0;
for (let i=0; i<a.length; i++){
 if(a[i]>0){
 count++;
 }else if(a[i]<0)
 {
 count--;
 }else
 {
 zeros++;
 } 
}
console.log("Difference between the number of +ves and -ves ", count);
console.log("Number of zeros ", zeros);

//for in
{
    let a = [8,2,3,-1,4,12,33,21,-12,-5,20, 101, -91];
    let count = 0;
    for (let i in a){
    if(a[i]>=-10 && a[i]<=10){
    count++;
    }
    }
    console.log("Number of elements between -10 and 10: ", count);
}

//for of 
{
let a = [8,2,3,-1,4,12,33,21,-12,-5,20, 101, -91];
let count = 0;
for (let num of a){
 if(num>=-10 && num<=10){
 count++;
 }
}
console.log("Number of elements between -10 and 10: ", count);
}

//while 
{
let a = [8,2,3,-1,4,12,33,21,-12,-5,20, 101, -91];
let count = 0;
let i = 0;
while (i<a.length){
 if(a[i]>=-10 && a[i]<=10){
 count++;
 }
 i++;
}
console.log("Number of elements between -10 and 10: ", count);
}

//functions 
function countAround0(a, range)
{
 let count = 0;
 let nrange = -range;
 for (let num of a){
 if(num>=nrange && num<=range){
 count++;
 }
 }
 return count;
}

let b = [8,2,3,-1,4,12,33,21,-12,-5,20, 101, -91];
range = 10;
console.log("Number of elements between ", -range, " and ", range, ": ", 
countAround0(b, 10));

//nested functions
function countAround0(a, range)
{
    function inRange(x, r){
        return (x>=-r && x<=r);
    }
    let count = 0;
    for (let num of a){
    if(inRange(num, range))
    {
    count++;
    }
    }
    return count;
}
let c = [8,2,3,-1,4,12,33,21,-12,-5,20, 101, -91];
range = 10;
console.log("Number of elements between ", -range, " and ", range, ": ", 
countAround0(c, 10))

//fucntions as properties of objects
let human = {
    name: "Sarim Baig",
    email: "s.baig@imperial.ac.uk",
    numOfModules: 4,
    introCard: function ()
    {
    return "Name: "+ this.name + "\n" + "Email: " + this.email + "\n";
    }
};
console.log(human.introCard());

//functions as data 
function getAreaComputation(shape_type)
{
 if(shape_type=="circle"){
 return function(r){return Math.PI*r*r;}
 }
 if(shape_type=="rectangle")
 {
 return function(l,w){return l*w};
 }
}
area = getAreaComputation("circle");
console.log("Area of a circle with radius 3: ", area(3));
area = getAreaComputation("rectangle");
console.log("Area of a circle with radius 3: ", area(3, 5));

//this - global object
let ans = 0;
function summation(x, y)
{
 this.ans = x+y;
}
console.log("Golbal ans: ", ans)

//this - inside objects
let blog = {
    name: 'Tapas',
    address: 'freecodecamp',
    message: function() {
        console.log("Name: ",this.name, "\nAddress: ", this.address);
    }
   };
blog.message();

//this - being reassigned to the appropriate object’s context
function greeting(obj) {
    obj.logMessage = function() {
    console.log(this.name, "is", this.age, " years old!");
    }
   };
   const tom = {
    name: 'Tom',
    age: 7
   };
   const jerry = {
    name: 'jerry',
    age: 3
   };
   greeting(tom);
   greeting(jerry);
   tom.logMessage ();
   jerry.logMessage ();

//classes 
class Person{
    constructor(n, e, g){
    this.name=n;
    this.email=e;
    this.gender=g;
    }
    introCard()
    {
    return "Name: "+ this.name + " &"+ " Email: " + this.email + "\n";
    }
   };
let person2 = new Person("Sarim Baig", "s.baig@imperial.ac.uk",'M');
console.log(person2.introCard());