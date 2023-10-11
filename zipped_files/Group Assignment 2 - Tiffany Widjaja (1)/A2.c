#include <stdio.h>

char num_to_letter (float score)
/* Converts a score into its alphabetical equivalent.
   Returns a char A, B, C, D, E, or Z when input is not valid.
   Args: score as a float */
{
    const short int MIN_A = 85, 
                    MIN_B = 75,
                    MIN_C = 65,
                    MIN_D = 55,
                    MIN_E = 0;
    if (score > 100) return 'Z'; // return 'Z' as invalid input
    if (score > MIN_A) return 'A';
    if (score > MIN_B) return 'B';
    if (score > MIN_C) return 'C';
    if (score > MIN_D) return 'D';
    if (score >= MIN_E) return 'E';
    return 'Z'; // return 'Z' as invalid input
}

char* pass_or_fail (float score)
/* Determine whether a student passes or fails.
   Returns "PASS" or "FAIL" as a string. 
   Args: score as a float */
{
    const short int PASSING_SCORE = 65;
    return (score > PASSING_SCORE) ? "PASS" : "FAIL";
}

int main()
{
    // Weight for grading. (Can be re-adjusted)
    // Default scores are adjusted according to BINUS' LMS
    const short int QUIZ_WEIGHT = 15,           // 'Kuis'
                    ASSIGNMENT_WEIGHT = 35,     // 15 (Group) + 20 (Personal) 
                    ATTENDANCE_WEIGHT = 10,     // 'Absensi'
                    PRACTICAL_EXAM_WEIGHT = 10, // Forum???
                    FINAL_EXAM_WEIGHT = 30;     // 'Ujian Akhir Semester'

    char continue_state = 'Y';
    int students_inputed = 0;
    float average_WAM = 0;

    // Make a loop! :) This way we can input as many students as we want.
    while (continue_state == 'Y' || continue_state == 'y')
    {
        char name[120] = {0};
        float score_quiz = 0, 
              score_assignment = 0,    
              score_attendance = 0,
              score_practical = 0,
              score_final = 0,
              WAM = 0; // Weighted Average Mark
        
        // Ask for user input.
        printf("Enter the student's name (max 120 characters): ");
        scanf("%s", name);

        printf("Enter average quiz score: ");
        scanf("%f", &score_quiz);
        printf("Enter average assignment score: ");
        scanf("%f", &score_assignment);
        printf("Enter average attendance score: ");
        scanf("%f", &score_attendance);
        printf("Enter average practical exam score: ");
        scanf("%f", &score_practical);
        printf("Enter final exam score: ");
        scanf("%f", &score_final);
        
        // Calculate the Weighted Average Mark (WAM).
        WAM =  (score_quiz * QUIZ_WEIGHT 
              + score_assignment * ASSIGNMENT_WEIGHT 
              + score_attendance * ATTENDANCE_WEIGHT 
              + score_practical * PRACTICAL_EXAM_WEIGHT 
              + score_final * FINAL_EXAM_WEIGHT) 
              / (QUIZ_WEIGHT + ASSIGNMENT_WEIGHT + ATTENDANCE_WEIGHT + PRACTICAL_EXAM_WEIGHT + FINAL_EXAM_WEIGHT);

        // Print results.
        printf("%s. %s's Weighted Average Score is %.2f (%c).\n", pass_or_fail(WAM), name, WAM, num_to_letter(WAM));
        printf("Quizzes \t%c\n"
               "Assignments \t%c\n"
               "Attendance \t%c\n"
               "Practicals \t%c\n"
               "Final exam \t%c\n", 
               num_to_letter(score_quiz), 
               num_to_letter(score_assignment), 
               num_to_letter(score_attendance), 
               num_to_letter(score_practical), 
               num_to_letter(score_final));

        // (Re-)calculate average WAM.
        students_inputed++;
        average_WAM = ((average_WAM * (students_inputed - 1)) + WAM)
                      / (float)students_inputed;

        // Ask if you want to add another student.
        printf("Do you want to add another student? (Y/N...): ");
        scanf(" %c", &continue_state);
    }

    printf("You have inputed %d student(s), and their average WAM is %.2f", students_inputed, average_WAM);

    return 0;
}