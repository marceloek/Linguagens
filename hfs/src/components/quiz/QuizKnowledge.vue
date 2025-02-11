<template>
  <div>
    <QuizQuestion
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
import questions from './questions'
import QuizQuestion from './QuizQuestion.vue'
import QuizResults from './QuizResults.vue'

export default {
  components: {
    QuizQuestion,
    QuizResults,
  },
  data: () => {
    return {
      questions: questions,
      currentQuestionIndex: 0,
      finished: false,
      answers: [],
    }
  },
  computed: {
    currentQuestion: function () {
      return this.questions[this.currentQuestionIndex]
    },
  },
  methods: {
    nextQuestion: function () {
      if (this.currentQuestionIndex === questions.length - 1) {
        console.log('index is', this.currentQuestionIndex, this.finished)

        this.finished = true
      } else {
        this.currentQuestionIndex++
      }
    },
    onComplete: function (result) {
      console.log('completedddd', result)
      this.answers.push(result)
      this.nextQuestion()
    },
    restartQuiz: function () {
      console.log('hellooooo')
      this.finished = false
      this.currentQuestionIndex = 0
      this.answers = []
    },
  },
}
</script>
