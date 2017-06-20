int main () {

   char grade = 'B';
   int i;

   switch(grade) {
      case 'A' :
         i = 1;
         break;
      case 'B' :
         grade = 'c';
         break;
      case 'C':
         i = 5;
         break;
      default :
         i = 6;
         break;
   }

   return grade;
}
