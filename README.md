# Command Line "Lines" Game: A C Programming Project
#### Video Demo:  <URL HERE>
#### Description:
 The Command Line "Lines" Game is a programming project developed in C, aiming to provide an engaging and challenging gaming experience. Inspired by the classic game "Lines," this project combines strategic thinking, pattern recognition, and logical reasoning. The objective of the game is to score as many points as possible by forming lines of five or more balls of the same color, either vertically, horizontally, or diagonally. This description will explore the reasons behind choosing C as the programming language for this project and highlight its features and gameplay mechanics.

Reasons for Choosing C:
C, known for its efficiency and versatility, was the preferred programming language for this project for several reasons:

1. Performance: C offers low-level control over system resources, allowing for optimized memory management and efficient execution. This is particularly crucial for a game that    requires real-time processing and responsiveness.

2. Portability: C programs can be easily compiled and run on various platforms, making it an ideal choice for a command line game that aims to reach a wide range of users. The ability to run on different operating systems enhances the game's accessibility and potential user base.

3. Integration: C has excellent integration capabilities with other languages and libraries. This allows for the incorporation of additional functionalities, such as input/output handling, user interface enhancements, and performance optimizations.

Gameplay Mechanics:
The Command Line "Lines" Game follows these fundamental mechanics:

1. Grid Setup: The game presents a 9x9 grid where players place balls of different colors. The grid serves as the playing field for forming lines.

2. Ball Placement: Players select a position on the grid to place a ball of a chosen color. The objective is to strategically position balls to create lines of five or more of the same color.

3. Line Formation: Whenever a line of five or more balls of the same color is formed—whether vertically, horizontally, or diagonally—the balls are removed from the grid, and the player earns points. The remaining balls above the cleared line cascade down to fill the gaps.

4. Random Ball Generation: After each move, the game generates new balls of random colors and places them on the grid. The player must plan their moves strategically to create and clear lines efficiently.

5. Game Over: The game ends when the entire 9x9 grid is filled with balls, and no more moves are possible. At this point, the player's score is calculated based on the number of lines formed and their lengths.

In developing the Command Line "Lines" Game, I decided to utilize linked lists as the primary data structure due to my personal interest and curiosity to delve deeper into their implementation. By incorporating linked lists into this project, I aimed to gain a firsthand understanding of this essential data structure in computer science and expand my programming skills through practical application. The choice to use linked lists reflects my dedication to self-improvement and my eagerness to explore and enhance my knowledge in the field.

Developing game was both challenging and rewarding. The implementation process required careful consideration of various aspects, such as grid management, line formation logic, and user interactions. It took me approximately 13 hours to complete the initial setup of the game, including the creation of the linked list structure and integrating it into the overall gameplay mechanics. The challenge lay in efficiently managing the grid using linked lists while ensuring seamless ball placement, line detection, and cascading effects. However, overcoming these challenges and witnessing the game come to life within a short timeframe was incredibly fulfilling and showcased the effectiveness of using linked lists in this project.
