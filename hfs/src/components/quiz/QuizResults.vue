<template>
  <!-- <div>
    <p>Você acertou {{ correctCount }} de {{ questionCount }} </p>
    <ul>
      <li v-for="(answer, index) in answers" :key="index">{{ answer }}</li>
    </ul>
  </div>-->
  <div class="card mt-4 mb-4">
    <div class="card-body">
      <h3>
        Você acertou
        <span class="font-weight-bolder text-success">{{ correctCount }}</span> de
        <span class="font-weight-bolder text-primary">{{ questionCount }}</span>
      </h3>
      <button class="btn btn-outline-secondary mt-4" v-on:click="restartQuiz()">Tente de novo!</button>
    </div>
  </div>
</template>

<script>
export default {
  name: "QuizResults",
  props: {
    answers: Array,
    restartQuiz: Function
  },
  computed: {
    questionCount: function() {
      return this.answers.length;
    },
    correctCount: function() {
      return this.answers.filter(a => a).length;
    }
  }
};
</script>
