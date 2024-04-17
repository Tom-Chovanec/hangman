using System;

namespace HelloWorld
{
    class Program
    {
        static void Main(string[] args)
        {
            int numberInt = 5; // Whole integer, +- 2,147,483,647 , number ends with nothing   toInt32
            long numberLong = 100L; // Whole integer, +- 9,223,372,036,854,775,808 , number ends with L    toInt64 
            float numFloat = 31.4F; // Fractions, 6 t 7 decimals , number ends with F
            double numberDouble = 10D; // Fractions, 15 decimals , number ends with D
            bool boolTrue = true; // 1 bit, stores true or false
            char character = 'a'; // 2 bits, stores one character
            string stringText = "AaBb"; // 2 bits per character, stores strings

            //----------------------------------------------------

            string firstEnter = "Enter your first name: ";
            string lastEnter = "Enter your last name: ";
            string nicknameEnter = "Enter your nickname: ";
            string passEnter = "Enter your password: ";

            Console.WriteLine("Welcome!");

            Console.Write(firstEnter);
            string firstname = Console.ReadLine();

            Console.Write(lastEnter);
            string lastname = Console.ReadLine();

            Console.Write(nicknameEnter);
            string username = Console.ReadLine();

            Console.Write(passEnter);
            string password = Console.ReadLine();

            Console.WriteLine(" ");
            Console.WriteLine($"Your name is: {firstname} {lastname}");
            Console.WriteLine("Your nickname is: " + username);
            Console.WriteLine($"Your password is {password.Length} characters long. It starts with {password[0]}.");

        }
    }
}
