
Local Toolchain + Build:
    - working Makefile that build MSP430 project
Git Best Practices
    - Use feature branches for changes 
    - Clean commit history using conventional commits 
Docker Environment
    - A custom Docker image with MSP430 GCC toolchain installed 
    - Pushed to Docker Hub for resuse in CI 
GitHub CI Setup 
    - .github/workflows/ci.yml
        -> Runs on push 
        -> Uses your Docker container 
        -> make 
        -> push to GitHub  

Git + CI development Workflow 
    - create a new branch locally
    - make code changes 
    - run make to build code 
    - commit changes 
    - push branch to github 
    - open a pull request 
    - CI runs atuomatically (runs inside docker container, esecutes make and make static)
    - If CI passes, can merge PR 

Install Docker
Create a Dockerfile - text file tells docker how to build the image
    - based image (22.04)
    - commands to install packages (wget, tar)
Download your toolchain inside the container 
    - Download the MSP430 GCC toolchain from TI's website
    - Extract it 
    - Move the support files into the include folder 
    - CLean up leftover install files 
Commit the container as an image 
Push to Docker Hub 

Why: Environment consistency (same compiler), lightwight & reproducible CI builds

 

YAML file:
    - a human-readable way to strcutre data - often used for configuration files 
    - "YAML Ain't Markup Language"
    - Like JSON but simpler and easier to read 
Core Concepts
    - Key-Value -> name: Terence (variable or setting)
    - Nested Data -> person: name: Terence (name is inside person)
    - List/Array -> - apple, - banana, -orange (list of items)
    - Indendation -> 2 spaces (used for nesting)






