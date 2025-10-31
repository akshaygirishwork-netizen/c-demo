pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh 'gcc main.c -o hello'
            }
        }
        stage('Run') {
            steps {
                sh './hello'
            }
        }
    }
}

