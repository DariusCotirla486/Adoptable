The 'adoptable_app' folder contains the code's source files written entirely in C++.

Adoptable is a C++/Qt application that implements a dual-mode system:
  - Admin mode: Allows CRUD operation to manage a list of pets and their data
  - User mode: Displays a showcase of available pets for adoption, enabling users to pick whether they adopt it or skip it. The selected list is then saved to a file.

Key features:
  - View-Controller-Repository-Model Architecture – A well-structured design that enhances maintainability and scalability.
  - Object-Oriented Architecture – Uses classes for pets, users, repositories, and GUI components, ensuring modularity and code reusability.
  - Intuitive Qt GUI – Dynamically generates windows and interactive elements using C++, providing a seamless user experience.
  - Robust Data Validation – Ensures accurate input handling and prevents errors.
  - Flexible File Export – Saves the user's adopted pet list in either CSV or HTML format, based on user preference.

Technologies used: C++, Qt
