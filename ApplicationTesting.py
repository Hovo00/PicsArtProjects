import subprocess as sub
import yaml
from pprint import pprint
import os

def getResultFromString(output):
    return (output.split(':')[-1]).strip()

def runTestCase(case):
    program = './expression_evaluator "' + case + '"' + '> res.txt'
    sub.run(program, shell = True)
    with open("res.txt", "r") as file:
        output = file.read()
    return getResultFromString(output)

def getTestCasesFromFile():
    filePath = "../testCases.yaml"
    with open(filePath, "r") as file:
        testCases = yaml.load(file, Loader=yaml.FullLoader)
    return testCases

def printFailedCase(testCases, case, receivedResult):
    print(case  + " - Failed")
    print("     Expression : " + testCases[case]["expression"])
    print("     Expected : " + testCases[case]["expected"])
    print("     Received : " + receivedResult)

def runAllCases(testCases):
    for testCase in testCases:
        result = runTestCase(testCases[testCase]["expression"])
        if result != testCases[testCase]["expected"]:
            printFailedCase(testCases, testCase, result)

testCases = getTestCasesFromFile()
runAllCases(testCases)
