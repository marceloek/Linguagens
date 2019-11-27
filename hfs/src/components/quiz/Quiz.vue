<template>
  <div>
    <Question
      v-if="!finished"
      :title="currentQuestion.title"
      :alternatives="currentQuestion.alternatives"
      :onComplete="onComplete"
      :key="currentQuestionIndex"
    />
    <QuizResults v-else :answers="answers" :restartQuiz="restartQuiz" />
  </div>
</template>

<script>
import questions from "./questions";
import Question from "./Question";
import QuizResults from "./QuizResults";

export default {
  components: {
    Question,
    QuizResults
  },
  name: "Quiz",
  data: () => {
    return {
      questions: questions,
      currentQuestionIndex: 0,
      finished: false,
      answers: []
    };
  },
  computed: {
    currentQuestion: function() {
      return this.questions[this.currentQuestionIndex];
    }
  },
  methods: {
    nextQuestion: function() {
      if (this.currentQuestionIndex === questions.length - 1) {
        // eslint-disable-next-line
        console.log("index is", this.currentQuestionIndex, this.finished);

        this.finished = true;
      } else {
        this.currentQuestionIndex++;
      }
    },
    onComplete: function(result) {
      // eslint-disable-next-line
      console.log("completedddd", result);
      this.answers.push(result);
      this.nextQuestion();
    },
    restartQuiz: function() {
      // eslint-disable-next-line
      console.log("hellooooo");
      this.finished = false;
      this.currentQuestionIndex = 0;
      this.answers = [];
    }
  }
};
</script>