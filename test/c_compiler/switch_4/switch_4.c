int main () {

   char grade = 'B';
   int i = 20;

   switch(i) {
      case 1 :
         i = 1;
      case 2 :
         grade = 'C';
         grade = 'D';
      case 20 :
         i = 5;
         grade = 'p';
         int i;
         break;
      default :
         i = 7;
         break;
   }

   switch(grade) {
      case 'A' :
         i = 1;
      case 'B' :
         grade = 'C';
         grade = 'D';
      case 'C' :
         i = 5;
         grade = 'p';
         int i;
         break;
      default :
         i = 7;
         grade = 'l';
         break;
   }

   return i + grade;
}
